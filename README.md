# TestSenior

Prueba Técnica de Page Personnel

# Módulos o Librerias

## Interfaces

```cpp
struct IDataGenerator
{
    std::byte GetRandomByte() const noexcept;
    std::byte GetRandomByte(const std::byte max) const noexcept;
    std::byte GetRandomByte(const std::byte min, const std::byte max) const noexcept;
    std::vector<std::byte> GetRandomBytes(std::size_t count) const noexcept;
    std::int32_t GetRandomNumber(const int32_t max) const noexcept;
    std::int32_t GetRandomNumber(const int32_t min, const int32_t max) const noexcept;
};
```

```cpp
struct IDataSearchEngine
{
    std::optional<int32_t> Search(const std::vector<std::byte>& source, const std::vector<std::byte> values_to_search) const noexcept;
};
```

```cpp
struct IDataPrintingEngine
{
    void Print(const std::byte data) const noexcept;
    void Print(const std::time_t data) const noexcept;
    void Print(const std::vector<std::byte>& data) const noexcept;
    void Print(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept;
    void Print(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept;
    void PrintLine(const std::byte data) const noexcept;
    void PrintLine(const std::time_t data) const noexcept;
    void PrintLine(const std::vector<std::byte>& data) const noexcept;
    void PrintLine(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept;
    void PrintLine(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept;
};
```

```cpp
struct IModule
{
    IDataGenerator& GetGenerator() const noexcept;
    IDataSearchEngine& GetSearchEngine() const noexcept;
    IDataPrintingEngine& GetPrintingEngine() const noexcept;
    void SetGenerator(std::unique_ptr<IDataGenerator>&& generator) noexcept;
    void SetSearchEngine(std::unique_ptr<IDataSearchEngine>&& search_engine) noexcept;
    void SetPrintingEngine(std::unique_ptr<IDataPrintingEngine>&& printing_engine) noexcept;
    void RunAsync() noexcept;
    void StopAsync() noexcept;
    void WaitForAsync(const std::chrono::milliseconds& milliseconds) const noexcept;
    void PrintResults() const noexcept;
};
```

## Ejemplo de uso

```cpp
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
```

## Secuencia de ejecución

```
                  ┌─────────────┐
                  |  Run Async  |
                  └──────┬──────┘
                         │
                         │
                         │
                         │                            ┌─────────────┐
                         │                      ┌─────┤ Thread.Join |
                         │                      |     └─────────────┘
                  ┌──────┴───────┐              |
                  | Clear Thread ├──────────────┤
                  └──────┬───────┘              |
                         |                      |     ┌───────────────────────────┐
                         |                      └─────┤ Cancelation Thread: False |
                         |                            └───────────────────────────┘
                         |
                         |
                         |
                         |
                  ┌──────┴────────┐
                  | Clear Results |
                  └──────┬────────┘
                         |
                         |                                                               ┌────────────────────────────────────────────────┐
                         |                                                               |                                                |
                         |                                                               |   ┌────────────────────────────────────────┐   |
                         |                                                               |   | IDataGenerator.GetRandomNumber(1, 100) |   |
                         |                                                               |   └───────────────────┬────────────────────┘   |
                         |                                                               |                       |                        |
                         |                                                               |                       v                        |
                   ┌─────┴─────┐              ┌───────────────────────────┐              |       ┌───────────────────────────────┐        |
                   | InputData ├──────────────┤ Generate 100 Input Buffer ├──────────────┤       | IDataGenerator.GetRandomBytes |        |
                   └─────┬─────┘              └───────────────────────────┘              |       └───────────────┬───────────────┘        |
                         |                                                               |                       |                        |
                         |                                                               |                       v                        |
                         |                                                               |                ┌──────────────┐                |
                         |                                                               |                │ Input Buffer │                |
                         |                                                               |                └──────────────┘                |
                         |                                                               |                                                |
                         |                                                               └────────────────────────────────────────────────┘
      ┌──────────────────┴─────────────────────┐
      | Calculate the number of threads to run |
      └──────────────────┬─────────────────────┘                             ┌──────────────────────────────┐
                         |                                                   |                              |
                         |                                                   |                              |
                         |                                                   |              ┌───────────────┴───────────────┐
                         |                                                   |              | IsThreadCancellationRequested | <──────────────────────────────────────────────────┐
                         |                                                   |              └───────────────┬───────────────┘                                                    |
                         |                                                   |                              |                                                                    |
                         |                                                   |                              |                                                                    |
                         |                                                   |                              |                                                                    |
                 ┌───────┴─────────┐              ┌───────────┐              |                              |                                                                    |
                 | Thread Function ├──────────────| InputData ├──────────────┘               ┌──────────────┴──────────────┐                                                     |
                 └───────┬─────────┘              └───────────┘                              |                             |                                                     |
                         |                                                             ┌─────┴─────┐                 ┌─────┴─────┐                                               |
                         |                                                             |    Yes    |                 |     No    |                                               |
                         |                                                             └─────┬─────┘                 └─────┬─────┘                                               |
                         |                                                                   |                             │                                                     |
                         |                                                                   |                             │                                                     |
                         |                                                                   |                             │                                                     |
                         |                         ┌───────────────┐                         |                             │                                                     |
                         |                         | Finish Thread ├─────────────────────────┘                             │                                                     |
                         |                         └───────────────┘                                                       │                                                     |
                         |                                                                                                 │                                                     |
                         |                                                                         ┌───────────────────────┴────────────────────────┐                            |
                         |                                                                         |                                                |                            |
               ┌─────────┴────────┐                                                                |   ┌────────────────────────────────────────┐   |                            |
               | Wait 100 Seconds |                                                                |   | IDataGenerator.GetRandomNumber(1, 100) |   |                            |
               └─────────┬────────┘                                                                |   └───────────────────┬────────────────────┘   |                            |
                         |                                                                         |                       |                        |                            |
                         |                                                                         |                       v                        |                            |
                         |                                                                         |       ┌───────────────────────────────┐        |                            |
                         |                                                                         ┤       | IDataGenerator.GetRandomBytes |        |                            |
                         |                                                                         |       └───────────────┬───────────────┘        |                            |
                         |                                                                         |                       |                        |                            |
                         |                                                                         |                       v                        |                            |
                         |                                                                         |              ┌──────────────────┐              |                            |
           ┌─────────────┴───────────────┐                                                         |              │ Data For Results │              |                            |
           | SetThreadCancellation(true) |                                                         |              └──────────────────┘              |                            |
           └─────────────┬───────────────┘                                                         |                                                |                            |
                         |                                                                         └───────────────────────┬────────────────────────┘                            |
                         |                                                                                                 │                                                     |
                         |                                                                                                 │                                   ┌───────────┐     |
                         |                                                                                                 │                               ┌───┤ Not Found ├─────┴──────────────────────────────────────────────┐
                         |                            ┌─────────────┐                                                      │                               |   └───────────┘                                                    |
                         |                      ┌─────┤ Thread.Join |                                                      │                               |                                                                    |
                         |                      |     └─────────────┘                                                      │                               |                                                                    |
                  ┌──────┴───────┐              |                                                                          │                 ┌─────────────┴────────────┐                 ┌───────┐                 ┌───────────┴──────────┐
                  | Clear Thread ├──────────────┤                                                                          └─────────────────┤ Search Data In InputData ├─────────────────┤ Found ├─────────────────┤ Save Data In Results |
                  └──────┬───────┘              |                                                                                            └──────────────────────────┘                 └───────┘                 └──────────────────────┘
                         |                      |     ┌───────────────────────────┐
                         |                      └─────┤ Cancelation Thread: False |
                         |                            └───────────────────────────┘
                         |
                         |
                         |
                         |
                 ┌───────┴───────┐
                 | Print Results |
                 └───────┬───────┘
                         |
                         |
                         |
                         |
                         |
                         |
                         |
                    ┌────┴───┐
                    | Finish |
                    └────────┘
```