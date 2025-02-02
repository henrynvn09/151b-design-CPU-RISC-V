// Copyright © 2019-2023
// 
// Licensed under the Apache License;
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>
#include <memory>
#include <set>
#include <simobject.h>
#include "debug.h"
#include "types.h"
#include "emulator.h"
#include "pipeline.h"

namespace tinyrv {

class ProcessorImpl;
class Instr;
class RAM;

class Core : public SimObject<Core> {
public:
  struct PerfStats {
    uint64_t cycles;
    uint64_t instrs;

    PerfStats() 
      : cycles(0)
      , instrs(0)
    {}
  };

  Core(const SimContext& ctx, uint32_t core_id, ProcessorImpl* processor);
  ~Core();

  void reset();

  void tick();

  void attach_ram(RAM* ram);

  bool running() const;

  bool check_exit(Word* exitcode, bool riscv_test) const;

  void showStats();

private:

  void if_stage();
  void id_stage();
  void ex_stage();
  void mem_stage();
  void wb_stage();

  uint32_t core_id_;
  ProcessorImpl* processor_;
  Emulator emulator_;
  
  PipelineLatch if_id_latch_;
  PipelineLatch id_ex_latch_;
  PipelineLatch ex_mem_latch_;
  PipelineLatch mem_wb_latch_;

  bool fetch_stalled_;  
  uint64_t issued_instrs_;
  
  // student added
  int32_t branch_stall;

  PerfStats perf_stats_;

  friend class Emulator;
};

} // namespace tinyrv
