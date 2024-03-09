// Copyright 2024 blaise
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <assert.h>
#include <util.h>
#include "types.h"
#include "core.h"
#include "debug.h"
#include "pipeline.h"

using namespace tinyrv;

GShare::GShare()
{
  //--
  this->BHR = 0;

  for (int i = 0; i < 256; i++)
  {
    this->BHT[i] = 0;
    this->BTB[i].valid = false;
    this->BTB[i].tag = (Word)-1;
    this->BTB[i].target = (Word)-1;
  }
}

GShare::~GShare()
{
  //--
}

bool GShare::predict(pipeline_trace_t *trace)
{
  // TODO: Implement GShare predictor
  // Your GShare's predict() method should first determine
  // the current predicted outcome, and then update the predictor.
  // also note that a successful prediction is a combination
  // of branch direction and branch target hits.
  // ============= BTB =============
  int index_bits = 8;
  Word pc_index = (trace->PC >> 2) & 0b11111111;
  Word pc_tag = (trace->PC >> 2) >> index_bits;

  //     1) Read current predictor states (BTB, BHR, BHT)
  //        You need to obtain predicted_nextPC from BTB
  //        you need to obtain predicted_taken from BHR and BHT

  BTB_item *btb = &BTB[pc_index]; // current btb state

  uint32_t bht_index = (BHR ^ pc_index) & 0b11111111;

  bool predicted_taken = (BHT[bht_index] >= 2) ? 1 : 0;

  //     2) Evaluate the prediction if correct, should return this result
  //        Should match actual_taken and actual_nextPC with predicted values.
  //        Note that we only match nextPC when we are predicting taken.

  // not sure if this is correct
  // Two cases: if predict taken, nextPC is obtained from BTB only when the
  // currentPC's tag match with the one from BTB, otherwise nextPC = currentPC+4
  // if predict not taken, nextPC = currentPC + 4
  Word predicted_nextPC;
  bool correctly_predicted; //= predicted_taken && (trace->isTaken == predicted_taken) && (trace->nextPC == btb->target);

  if (pc_tag == btb->tag)
  {
    predicted_nextPC = btb->target;
  }
  else
  {
    predicted_nextPC = trace->PC + 4;
  }

  correctly_predicted = (trace->isTaken && predicted_taken && trace->nextPC == predicted_nextPC) || (!trace->isTaken && !predicted_taken);

  // ========= print out ==============
  std::string rd_text = (trace->wb) ? (", rd=x" + std::to_string(trace->rd)) : "";
  DP(3, "*** GShare: BHR=0x" << std::hex << (int)BHR << ", PHT_index=" << (bht_index) << ", PHT_taken=" << std::dec << BHT[bht_index] << ", BTB_nextPC=0x" << std::hex << btb->target << ": PC=0x" << std::hex << trace->PC << ", wb=" << trace->wb << rd_text << ", ex=" << trace->fu_type << " (#" << std::dec << trace->uuid << ")");

  // print all variable to debug

  DP(3, "*** GShare: predicted " << (predicted_taken ? "taken=" : "not-taken=") << std::dec << correctly_predicted << ": PC=0x" << std::hex << trace->PC << ", wb=" << trace->wb << rd_text << ", ex=" << trace->fu_type << " (#" << std::dec << trace->uuid << ")");

  //     3) Update predictor states (BTB, BHR, BHT)
  //        Update BTB with actual_nextPC if actual_taken is true
  //        Update BHR and BHT with actual_taken status (refer to lecture slide for the algorithm)

  // if actual_taken is true
  if (trace->isTaken)
  {

    BTB[pc_index] = {true, pc_tag, trace->nextPC};
    // // Update BTB with actual_nextPC if actual_taken is true
    // if (BTB[pc_index].valid == false || BTB[pc_index].tag != pc_tag)
    // {
    //   BTB[pc_index] = {true, pc_tag, (Word)trace->nextPC};
    // }
    // std::cout << std::hex << BTB[pc_index].target << " " << trace->PC << " " << pc_index << "========" << std::endl;

    if (BHT[bht_index] < 3)
    {
      BHT[bht_index]++;
    }
  }
  else
  {
    if (BHT[bht_index] > 0)
    {
      BHT[bht_index]--;
    }
  }

  BHR = ((BHR << 1) | trace->isTaken) & 0b11111111;

  return correctly_predicted;
}
