#include "Trace.h"
#include "Branch_Predictor.h"

extern TraceParser *initTraceParser(const char * trace_file);
extern bool getInstruction(TraceParser *cpu_trace);

extern Branch_Predictor *initBranchPredictor();
extern bool predict(Branch_Predictor *branch_predictor, Instruction *instr);

int main(int argc, const char *argv[])
{
    TraceParser *cpu_trace;
    if (argc == 2) {
        cpu_trace =  initTraceParser(argv[1]);
        set_script_parameters(4, 0, 0, 0, 0, 0);
    } else if(argc == 3) {
        cpu_trace =  initTraceParser(argv[2]);
        set_script_parameters(3, 0, 0, 0, atoi(argv[1]), 0);
    } else if(argc == 4) {
        cpu_trace =  initTraceParser(argv[3]);
        set_script_parameters(1, atoi(argv[1]), atoi(argv[2]), 0, 0, 0);
    } else if(argc == 5) {
        cpu_trace =  initTraceParser(argv[4]);
        set_script_parameters(2, 0, 0, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    } else {
        printf("Usage:\n");
        printf("Default 2-bit Local Predictor  \t%s <trace-file>\n", argv[0]);
        printf("Modified gShare Predictor      \t%s <global-predictor-size> <trace-file>\n", argv[0]);
        printf("Modified 2-Bit Local Predictor \t%s <local-predictor-size> <local-counter-bits> <trace-file>\n", argv[0]);
        printf("Modified Tournament Predictor  \t%s <local-history-table-size> <global-predictor-size> <choice-predictor-size> <trace-file>\n", argv[0]);
        return 0;
    }

    // Initialize a branch predictor
    Branch_Predictor *branch_predictor = initBranchPredictor();

    // Running the trace
    uint64_t num_of_instructions = 0;
    uint64_t num_of_branches = 0;
    uint64_t num_of_correct_predictions = 0;
    uint64_t num_of_incorrect_predictions = 0;

    while (getInstruction(cpu_trace))
    {
        // We are only interested in BRANCH instruction
        if (cpu_trace->cur_instr->instr_type == BRANCH)
        {
            ++num_of_branches;

            if (predict(branch_predictor, cpu_trace->cur_instr))
            {
                ++num_of_correct_predictions;
            }
            else
            {
                ++num_of_incorrect_predictions;
            }
        }
        ++num_of_instructions;
    }

    float performance = (float)num_of_correct_predictions / (float)num_of_branches * 100;

    printf("Number of correct predictions: %"PRIu64"\n", num_of_correct_predictions);
    printf("Number of incorrect predictions: %"PRIu64"\n", num_of_incorrect_predictions);
    printf("Predictor Correctness: %f%%\n", performance);

    //printf("%"PRIu64", %"PRIu64", %f\n", num_of_correct_predictions, num_of_incorrect_predictions, performance);
}
