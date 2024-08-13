#pragma once


#include <filesystem>
#include <memory>
#include <vector>
#include <string_view>

#include "partitioner.hpp"

namespace compress  {

  struct Configuration { 

    std::unique_ptr<BiPartitioner> partitioningStrategy = std::unique_ptr<BiPartitioner>{nullptr};
    std::filesystem::path graphPath = std::filesystem::current_path();
    int recursionDepth = -1; 

    Configuration() {}
   
    // deep copy polymorphic type using clone() method 
    Configuration(const Configuration& rhs) {
        


    }


    Configuration(Configuration&&) = default;
  };


  class CLIArgumentParser {
    private:
      Configuration lastConfiguration;
      std::vector<std::string> arguments;
      int argumentsProcessed;
      static constexpr std::string_view numberChars = "0123456789";

      void parsePartioningStrategyFromString(std::string parseFrom);

    public:

      CLIArgumentParser() : lastConfiguration(), arguments(), argumentsProcessed(0) {}
      explicit CLIArgumentParser(std::vector<std::string> _arguments) : lastConfiguration(),
      arguments(std::move(_arguments)), argumentsProcessed(arguments.size()) {} 

      CLIArgumentParser(const CLIArgumentParser&);
      

      Configuration parseConfiguration();
      void newArgument(const std::string& newArgument) {arguments.push_back(newArgument);}
   };



} // namespace compress