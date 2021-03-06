#include "HelpCommandFactory.hpp"
#include "HelpCommandKeys.hpp"
#include "HelpCommands.hpp"

HelpCommandFactory::HelpCommandFactory()
{
}

HelpCommandFactory::~HelpCommandFactory()
{
}

CommandPtr HelpCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;

  if (command_name == HelpCommandKeys::KEYBINDINGS)
  {
    command = std::make_shared<KeybindingsCommand>(key);
  }
  else if (command_name == HelpCommandKeys::EXIT_HELP)
  {
    command = std::make_shared<ExitHelpCommand>(key);
  }
  else if (command_name == HelpCommandKeys::INTRODUCTION_ROGUELIKES)
  {
    command = std::make_shared<IntroductionRoguelikesCommand>(key);
  }
  else if (command_name == HelpCommandKeys::SOTW_HISTORY)
  {
    command = std::make_shared<SOTWHistoryCommand>(key);
  }
  else if (command_name == HelpCommandKeys::STRATEGY_BASICS)
  {
    command = std::make_shared<StrategyBasicsCommand>(key);
  }
  else if (command_name == HelpCommandKeys::CASINO_GAMES)
  {
    command = std::make_shared<CasinoGamesCommand>(key);
  }

  return command;
}

CommandFactoryType HelpCommandFactory::get_factory_type() const
{
  return CommandFactoryType::COMMAND_FACTORY_TYPE_HELP;
}

CommandFactory* HelpCommandFactory::clone()
{
  return new CommandFactory(*this);
}

ClassIdentifier HelpCommandFactory::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/HelpCommandFactory_test.cpp"
#endif