#include "Main.hpp"

int32_t main([[maybe_unused]] const int32_t argc, [[maybe_unused]] const char* argv[])
{
    printf("C++ Version: %lu\n", __cplusplus);

    auto module = Program::Module::ModuleFactory::Create();

    module->SetGenerator(Program::Module::DataGeneratorFactory::Create());
    module->SetSearchEngine(Program::Module::DataSearchEngineFactory::Create());
    module->SetPrintingEngine(Program::Module::DataPrintingEngineFactory::Create());

    printf("Running...\n");
    module->RunAsync();

    printf("Waiting for 100 seconds...\n");
    module->WaitForAsync(std::chrono::seconds{ 100 });

    printf("Stopping...\n");
    module->StopAsync();

    module->PrintResults();
    return EXIT_SUCCESS;
}
