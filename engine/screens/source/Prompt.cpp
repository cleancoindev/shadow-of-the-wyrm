#include "Prompt.hpp"
#include "PromptTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

Prompt::Prompt(const PromptLocation prompt_location)
: location(prompt_location), type(PromptType::PROMPT_TYPE_CHARACTER), accept_any_input(false)
{
  initialize();
}

void Prompt::set_text_sid(const string& new_text_sid)
{
  text_sid = new_text_sid;
}

string Prompt::get_text_sid() const
{
  return text_sid;
}

string Prompt::get_text() const
{
  return StringTable::get(text_sid);
}

void Prompt::set_location(const PromptLocation new_location)
{
  location = new_location;
}

PromptLocation Prompt::get_location() const
{
  return location;
}

void Prompt::set_type(const PromptType new_type)
{
  type = new_type;
}

PromptType Prompt::get_type() const
{
  return type;
}

// This does all the work of setting up the prompt text, etc.
void Prompt::initialize()
{
  // Should be re-defined by all subclasses of prompt.
}

void Prompt::set_accept_any_input(const bool new_accept_any_input)
{
  accept_any_input = new_accept_any_input;
}

bool Prompt::get_accept_any_input() const
{
  return accept_any_input;
}

// AnyKeyPrompt

AnyKeyPrompt::AnyKeyPrompt() : Prompt(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT)
{
  initialize();
}

void AnyKeyPrompt::initialize()
{
  text_sid = PromptTextKeys::PROMPT_ANY_KEY;
}

// NullPrompt
NullPrompt::NullPrompt() : Prompt(PromptLocation::PROMPT_LOCATION_LOWER_RIGHT)
{
  initialize();
}

void NullPrompt::initialize()
{
  text_sid = "";
}

// TextPrompt

TextPrompt::TextPrompt() : Prompt(PromptLocation::PROMPT_LOCATION_DEFAULT)
{
  type = PromptType::PROMPT_TYPE_TEXT;
}

void TextPrompt::initialize()
{
  // JCD REMOVE THIS LATER IF NOT USED
}
