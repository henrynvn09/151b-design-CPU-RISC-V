TESTS_32I := $(filter-out rv32ui-p-ma_data.hex rv32ui-p-fence_i.hex, $(wildcard rv32ui-p-*.hex))
TESTS_32M := $(wildcard rv32um-p-*.hex)

all:

run-32ui:
	$(foreach test, $(TESTS_32I), ../tinyrv $(test) || exit;)

run-32um:
	$(foreach test, $(TESTS_32M), ../tinyrv $(test) || exit;)

run: run-32ui run-32um

clean: