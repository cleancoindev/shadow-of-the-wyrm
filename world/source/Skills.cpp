#include <sstream>
#include "Serialize.hpp"
#include "SkillFactory.hpp"
#include "Skills.hpp"
#include "SkillTextKeys.hpp"
#include "SkillTypes.hpp"
#include "StringTable.hpp"

using namespace std;

// Skill
Skill::Skill()
{
  initialize();
}

Skill::Skill(const SkillCategory new_category)
{
  initialize();
  category = new_category;
}

Skill& Skill::operator=(const Skill& skill)
{
  if (this != &skill)
  {
    this->category = skill.category;
    this->value = skill.value;
    this->marks = skill.marks;
    this->threshold = skill.threshold;
    this->skill_name_sid = skill.skill_name_sid;
    this->skill_increment_message_sid = skill.skill_increment_message_sid;
  }

  return *this;
}

bool Skill::operator==(const Skill& skill) const
{
  bool result = true;

  result = result && (category == skill.category);
  result = result && (value == skill.value);
  result = result && (marks == skill.marks);
  result = result && (threshold == skill.threshold);
  result = result && (skill_name_sid == skill.skill_name_sid);
  result = result && (skill_increment_message_sid == skill.skill_increment_message_sid);
  result = result && (internal_class_identifier() == skill.internal_class_identifier());

  return result;
}

Skill::Skill(const Skill& skill)
{
  *this = skill;
}

void Skill::initialize()
{
  category = SkillCategory::SKILL_CATEGORY_UNDEFINED;
  value = 0;
  threshold = 0;
}

// Set the value, and then also update the threshold for the new value.
void Skill::set_value(const int new_value)
{
  value = (new_value <= 100) ? new_value : 100;
  
  set_threshold_for_value(value);
}

int Skill::get_value() const
{
  return value;
}

bool Skill::is_learned() const
{
  return (value > 0);
}

// NWPs and magic skills can't be trained from unlearned.  Melee and ranged weapons can.
bool Skill::can_train_from_unlearned() const
{
  return false;
}

void Skill::increment_value()
{
  value++;
}

void Skill::set_marks(const Marks& new_marks)
{
  marks = new_marks;
}

Marks Skill::get_marks() const
{
  return marks;
}

Marks& Skill::get_marks_ref()
{
  return marks;
}

void Skill::set_threshold(const int new_threshold)
{
  threshold = new_threshold;
}

// By default, the threshold for a skill is the skill's value.
// Certain classes of skills (weapon skills, etc) may override this.
void Skill::set_threshold_for_value(const int skill_value)
{
  threshold = static_cast<int>(skill_value * get_threshold_multiplier());
}

int Skill::get_threshold() const
{
  return threshold;
}


float Skill::get_threshold_multiplier() const
{
  return 1.0f;
}

SkillCategory Skill::get_category() const
{
  return category;
}

void Skill::set_skill_name_sid(const string& new_skill_name_sid)
{
  skill_name_sid = new_skill_name_sid;
}

string Skill::get_skill_name_sid() const
{
  return skill_name_sid;
}

void Skill::set_skill_increment_message_sid(const string& new_skill_increment_message_sid)
{
  skill_increment_message_sid = new_skill_increment_message_sid;
}

string Skill::get_skill_increment_message_sid() const
{
  return skill_increment_message_sid;
}

// Shouldn't be used in-game - this is just a function for outputting the entire skill as a string.
string Skill::str() const
{
  ostringstream ss;

  ss << StringTable::get(skill_name_sid) << ": " << value;

  return ss.str();
}

bool Skill::serialize(ostream& stream) const
{
  Serialize::write_int(stream, value);
  Serialize::write_int(stream, threshold);
  Serialize::write_enum(stream, category);
  Serialize::write_string(stream, skill_name_sid);
  Serialize::write_string(stream, skill_increment_message_sid);
  marks.serialize(stream);

  return true;
}

bool Skill::deserialize(istream& stream)
{
  Serialize::read_int(stream, value);
  Serialize::read_int(stream, threshold);
  Serialize::read_enum(stream, category);
  Serialize::read_string(stream, skill_name_sid);
  Serialize::read_string(stream, skill_increment_message_sid);
  marks.deserialize(stream);

  return true;
}

// GeneralSkill
GeneralSkill::GeneralSkill() : Skill(SkillCategory::SKILL_CATEGORY_GENERAL)
{
}

// WeaponSkill
WeaponSkill::WeaponSkill() : Skill(SkillCategory::SKILL_CATEGORY_MELEE)
{
}

float WeaponSkill::get_threshold_multiplier() const
{
  return 2.0f;
}

bool WeaponSkill::can_train_from_unlearned() const
{
  return true;
}

// RangedWeaponSkill
RangedWeaponSkill::RangedWeaponSkill() : Skill(SkillCategory::SKILL_CATEGORY_RANGED)
{
}

bool RangedWeaponSkill::can_train_from_unlearned() const
{
  return true;
}

// MagicSkill
MagicSkill::MagicSkill() : Skill(SkillCategory::SKILL_CATEGORY_MAGIC)
{
}

// Individual Skills

// Archery
ArcherySkill::ArcherySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ARCHERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_ARCHERY_INCREMENT;
}

Skill* ArcherySkill::clone()
{
  return new ArcherySkill(*this);
}

ClassIdentifier ArcherySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_ARCHERY;
}

// Awareness
AwarenessSkill::AwarenessSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_AWARENESS_INCREMENT;
}

Skill* AwarenessSkill::clone()
{
  return new AwarenessSkill(*this);
}

ClassIdentifier AwarenessSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_AWARENESS;
}

// Bargaining
BargainingSkill::BargainingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BARGAINING_INCREMENT;
}

Skill* BargainingSkill::clone()
{
  return new BargainingSkill(*this);
}

ClassIdentifier BargainingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BARGAINING;
}

// Beastmastery
BeastmasterySkill::BeastmasterySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BEASTMASTERY_INCREMENT;
}

Skill* BeastmasterySkill::clone()
{
  return new BeastmasterySkill(*this);
}

ClassIdentifier BeastmasterySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BEASTMASTERY;
}

// Blind Fighting
BlindFightingSkill::BlindFightingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BLIND_FIGHTING_INCREMENT;
}

Skill* BlindFightingSkill::clone()
{
  return new BlindFightingSkill(*this);
}

ClassIdentifier BlindFightingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BLINDFIGHTING;
}

// Boating
BoatingSkill::BoatingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOATING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BOATING_INCREMENT;
}

Skill* BoatingSkill::clone()
{
  return new BoatingSkill(*this);
}

ClassIdentifier BoatingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BOATING;
}

// Bowyer
BowyerSkill::BowyerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BOWYER;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BOWYER_INCREMENT;
}

Skill* BowyerSkill::clone()
{
  return new BowyerSkill(*this);
}

ClassIdentifier BowyerSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BOWYER;
}

// Brewing
BrewingSkill::BrewingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_BREWING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_BREWING_INCREMENT;
}

Skill* BrewingSkill::clone()
{
  return new BrewingSkill(*this);
}

ClassIdentifier BrewingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BREWING;
}

// Cantrips
CantripsSkill::CantripsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CANTRIPS_INCREMENT;
}

Skill* CantripsSkill::clone()
{
  return new CantripsSkill(*this);
}

ClassIdentifier CantripsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_CANTRIPS;
}

// Carrying
CarryingSkill::CarryingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CARRYING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CARRYING_INCREMENT;
}

Skill* CarryingSkill::clone()
{
  return new CarryingSkill(*this);
}

ClassIdentifier CarryingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_CARRYING;
}

// Combat
CombatSkill::CombatSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_COMBAT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_COMBAT_INCREMENT;
}

Skill* CombatSkill::clone()
{
  return new CombatSkill(*this);
}

float CombatSkill::get_threshold_multiplier() const
{
  return 2.0f;
}

ClassIdentifier CombatSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_COMBAT;
}

// Crafting
CraftingSkill::CraftingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_CRAFTING_INCREMENT;
}

Skill* CraftingSkill::clone()
{
  return new CraftingSkill(*this);
}

ClassIdentifier CraftingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_CRAFTING;
}

// Desert Lore
DesertLoreSkill::DesertLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DESERT_LORE_INCREMENT;
}

Skill* DesertLoreSkill::clone()
{
  return new DesertLoreSkill(*this);
}

ClassIdentifier DesertLoreSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DESERT_LORE;
}

// Detection
DetectionSkill::DetectionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DETECTION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DETECTION_INCREMENT;
}

Skill* DetectionSkill::clone()
{
  return new DetectionSkill(*this);
}

ClassIdentifier DetectionSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DETECTION;
}

// Disarm Traps
DisarmTrapsSkill::DisarmTrapsSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DISARM_TRAPS_INCREMENT;
}

Skill* DisarmTrapsSkill::clone()
{
  return new DisarmTrapsSkill(*this);
}

ClassIdentifier DisarmTrapsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DISARM_TRAPS;
}

// Dual Wield
DualWieldSkill::DualWieldSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DUAL_WIELD_INCREMENT;
}

Skill* DualWieldSkill::clone()
{
  return new DualWieldSkill(*this);
}

ClassIdentifier DualWieldSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DUAL_WIELD;
}

// Dungeoneering
DungeoneeringSkill::DungeoneeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_DUNGEONEERING_INCREMENT;
}

Skill* DungeoneeringSkill::clone()
{
  return new DungeoneeringSkill(*this);
}

ClassIdentifier DungeoneeringSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DUNGEONEERING;
}

// Escape
EscapeSkill::EscapeSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_ESCAPE_INCREMENT;
}

Skill* EscapeSkill::clone()
{
  return new EscapeSkill(*this);
}

ClassIdentifier EscapeSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_ESCAPE;
}

// Foraging
ForagingSkill::ForagingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FORAGING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FORAGING_INCREMENT;
}

Skill* ForagingSkill::clone()
{
  return new ForagingSkill(*this);
}

ClassIdentifier ForagingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_FORAGING;
}

// Forest Lore
ForestLoreSkill::ForestLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FOREST_LORE_INCREMENT;
}

Skill* ForestLoreSkill::clone()
{
  return new ForestLoreSkill(*this);
}

ClassIdentifier ForestLoreSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_FOREST_LORE;
}

// Fishing
FishingSkill::FishingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FISHING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FISHING_INCREMENT;
}

Skill* FishingSkill::clone()
{
  return new FishingSkill(*this);
}

ClassIdentifier FishingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_FISHING;
}

// Fletchery
FletcherySkill::FletcherySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_FLETCHERY_INCREMENT;
}

Skill* FletcherySkill::clone()
{
  return new FletcherySkill(*this);
}

ClassIdentifier FletcherySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_FLETCHERY;
}

// Herbalism
HerbalismSkill::HerbalismSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HERBALISM_INCREMENT;
}

Skill* HerbalismSkill::clone()
{
  return new HerbalismSkill(*this);
}

ClassIdentifier HerbalismSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_HERBALISM;
}

// Hiding
HidingSkill::HidingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HIDING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HIDING_INCREMENT;
}

Skill* HidingSkill::clone()
{
  return new HidingSkill(*this);
}

ClassIdentifier HidingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_HIDING;
}

// Hunting
HuntingSkill::HuntingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_HUNTING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_HUNTING_INCREMENT;
}

Skill* HuntingSkill::clone()
{
  return new HuntingSkill(*this);
}

ClassIdentifier HuntingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_HUNTING;
}

// Intimidation
IntimidationSkill::IntimidationSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_INTIMIDATION_INCREMENT;
}

Skill* IntimidationSkill::clone()
{
  return new IntimidationSkill(*this);
}

ClassIdentifier IntimidationSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_INTIMIDATION;
}

// Jeweler
JewelerSkill::JewelerSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JEWELER;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_JEWELER_INCREMENT;
}

Skill* JewelerSkill::clone()
{
  return new JewelerSkill(*this);
}

ClassIdentifier JewelerSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_JEWELER;
}

// Jumping
JumpingSkill::JumpingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_JUMPING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_JUMPING_INCREMENT;
}

Skill* JumpingSkill::clone()
{
  return new JumpingSkill(*this);
}

ClassIdentifier JumpingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_JUMPING;
}

// Leadership
LeadershipSkill::LeadershipSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LEADERSHIP_INCREMENT;
}

Skill* LeadershipSkill::clone()
{
  return new LeadershipSkill(*this);
}

ClassIdentifier LeadershipSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_LEADERSHIP;
}

// Literacy
LiteracySkill::LiteracySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LITERACY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LITERACY_INCREMENT;
}

Skill* LiteracySkill::clone()
{
  return new LiteracySkill(*this);
}

ClassIdentifier LiteracySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_LITERACY;
}

// Lore
LoreSkill::LoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_LORE_INCREMENT;
}

Skill* LoreSkill::clone()
{
  return new LoreSkill(*this);
}

ClassIdentifier LoreSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_LORE;
}

// Magic
MagicGeneralSkill::MagicGeneralSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MAGIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MAGIC_INCREMENT;
}

float MagicGeneralSkill::get_threshold_multiplier() const
{
  return 2.0f;
}

Skill* MagicGeneralSkill::clone()
{
  return new MagicGeneralSkill(*this);
}

ClassIdentifier MagicGeneralSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MAGICGENERAL;
}

// Marsh Lore
MarshLoreSkill::MarshLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MARSH_LORE_INCREMENT;
}

Skill* MarshLoreSkill::clone()
{
  return new MarshLoreSkill(*this);
}

ClassIdentifier MarshLoreSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MARSH_LORE;
}

// Medicine
MedicineSkill::MedicineSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MEDICINE_INCREMENT;
}

Skill* MedicineSkill::clone()
{
  return new MedicineSkill(*this);
}

ClassIdentifier MedicineSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MEDICINE;
}

// Mountain Lore
MountainLoreSkill::MountainLoreSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAIN_LORE_INCREMENT;
}

Skill* MountainLoreSkill::clone()
{
  return new MountainLoreSkill(*this);
}

ClassIdentifier MountainLoreSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MOUNTAIN_LORE;
}

// Mountaineering
MountaineeringSkill::MountaineeringSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MOUNTAINEERING_INCREMENT;
}

Skill* MountaineeringSkill::clone()
{
  return new MountaineeringSkill(*this);
}

ClassIdentifier MountaineeringSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MOUNTAINEERING;
}

// Music
MusicSkill::MusicSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_MUSIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_MUSIC_INCREMENT;
}

Skill* MusicSkill::clone()
{
  return new MusicSkill(*this);
}

ClassIdentifier MusicSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MUSIC;
}

// Night Sight
NightSightSkill::NightSightSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_NIGHT_SIGHT_INCREMENT;
}

Skill* NightSightSkill::clone()
{
  return new NightSightSkill(*this);
}

ClassIdentifier NightSightSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_NIGHT_SIGHT;
}

// Oceanography
OceanographySkill::OceanographySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_OCEANOGRAPHY_INCREMENT;
}

Skill* OceanographySkill::clone()
{
  return new OceanographySkill(*this);
}

ClassIdentifier OceanographySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_OCEANOGRAPHY;
}

// Papercraft
PapercraftSkill::PapercraftSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_PAPERCRAFT_INCREMENT;
}

Skill* PapercraftSkill::clone()
{
  return new PapercraftSkill(*this);
}

ClassIdentifier PapercraftSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_PAPERCRAFT;
}

// Religion
ReligionSkill::ReligionSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_RELIGION;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_RELIGION_INCREMENT;
}

Skill* ReligionSkill::clone()
{
  return new ReligionSkill(*this);
}

ClassIdentifier ReligionSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_RELIGION;
}

// Scribing
ScribingSkill::ScribingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SCRIBING_INCREMENT;
}

Skill* ScribingSkill::clone()
{
  return new ScribingSkill(*this);
}

ClassIdentifier ScribingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SCRIBING;
}

// Skinning
SkinningSkill::SkinningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SKINNING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SKINNING_INCREMENT;
}

Skill* SkinningSkill::clone()
{
  return new SkinningSkill(*this);
}

ClassIdentifier SkinningSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SKINNING;
}

// Smithing
SmithingSkill::SmithingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SMITHING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SMITHING_INCREMENT;
}

Skill* SmithingSkill::clone()
{
  return new SmithingSkill(*this);
}

ClassIdentifier SmithingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SMITHING;
}

// Spelunking
SpelunkingSkill::SpelunkingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SPELUNKING_INCREMENT;
}

Skill* SpelunkingSkill::clone()
{
  return new SpelunkingSkill(*this);
}

ClassIdentifier SpelunkingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SPELUNKING;
}

// Stealth
StealthSkill::StealthSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_STEALTH;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_STEALTH_INCREMENT;
}

Skill* StealthSkill::clone()
{
  return new StealthSkill(*this);
}

ClassIdentifier StealthSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_STEALTH;
}

// Swimming
SwimmingSkill::SwimmingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_SWIMMING_INCREMENT;
}

Skill* SwimmingSkill::clone()
{
  return new SwimmingSkill(*this);
}

ClassIdentifier SwimmingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SWIMMING;
}

// Tanning
TanningSkill::TanningSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_TANNING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_TANNING_INCREMENT;
}

Skill* TanningSkill::clone()
{
  return new TanningSkill(*this);
}

ClassIdentifier TanningSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_TANNING;
}

// Thievery
ThieverySkill::ThieverySkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_THIEVERY_INCREMENT;
}

Skill* ThieverySkill::clone()
{
  return new ThieverySkill(*this);
}

ClassIdentifier ThieverySkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THIEVERY;
}

// Wandcraft
WandcraftSkill::WandcraftSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_WANDCRAFT;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_WANDCRAFT_INCREMENT;
}

Skill* WandcraftSkill::clone()
{
  return new WandcraftSkill(*this);
}

ClassIdentifier WandcraftSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_WANDCRAFT;
}

// Weaving
WeavingSkill::WeavingSkill()
: GeneralSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_GENERAL_WEAVING;
  skill_increment_message_sid = SkillTextKeys::SKILL_GENERAL_WEAVING_INCREMENT;
}

Skill* WeavingSkill::clone()
{
  return new WeavingSkill(*this);
}

ClassIdentifier WeavingSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_WEAVING;
}

// MELEE WEAPON SKILLS

// Axes
AxesSkill::AxesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_AXES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_AXES_INCREMENT;
}

Skill* AxesSkill::clone()
{
  return new AxesSkill(*this);
}

ClassIdentifier AxesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_AXES;
}

// Short Blades
ShortBladesSkill::ShortBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_SHORT_BLADES_INCREMENT;
}

Skill* ShortBladesSkill::clone()
{
  return new ShortBladesSkill(*this);
}

ClassIdentifier ShortBladesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SHORT_BLADES;
}

// Long Blades
LongBladesSkill::LongBladesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_LONG_BLADES_INCREMENT;
}

Skill* LongBladesSkill::clone()
{
  return new LongBladesSkill(*this);
}

ClassIdentifier LongBladesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_LONG_BLADES;
}

// Bludgeons
BludgeonsSkill::BludgeonsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_BLUDGEONS_INCREMENT;
}

Skill* BludgeonsSkill::clone()
{
  return new BludgeonsSkill(*this);
}

ClassIdentifier BludgeonsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BLUDGEONS;
}

// Daggers
DaggersSkill::DaggersSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_DAGGERS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_DAGGERS_INCREMENT;
}

Skill* DaggersSkill::clone()
{
  return new DaggersSkill(*this);
}

ClassIdentifier DaggersSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DAGGERS;
}

// Rods and Staves
RodsAndStavesSkill::RodsAndStavesSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_RODS_AND_STAVES_INCREMENT;
}

Skill* RodsAndStavesSkill::clone()
{
  return new RodsAndStavesSkill(*this);
}

ClassIdentifier RodsAndStavesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_RODS_AND_STAVES;
}

// Spears
SpearsSkill::SpearsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_SPEARS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_SPEARS_INCREMENT;
}

Skill* SpearsSkill::clone()
{
  return new SpearsSkill(*this);
}

ClassIdentifier SpearsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SPEARS;
}

// Unarmed
UnarmedSkill::UnarmedSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_UNARMED;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_UNARMED_INCREMENT;
}

Skill* UnarmedSkill::clone()
{
  return new UnarmedSkill(*this);
}

ClassIdentifier UnarmedSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_UNARMED;
}

// Whips
WhipsSkill::WhipsSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_WHIPS;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_WHIPS_INCREMENT;
}

Skill* WhipsSkill::clone()
{
  return new WhipsSkill(*this);
}

ClassIdentifier WhipsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_WHIPS;
}

// Exotic
ExoticMeleeSkill::ExoticMeleeSkill()
: WeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MELEE_EXOTIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_MELEE_EXOTIC_INCREMENT;
}

float ExoticMeleeSkill::get_threshold_multiplier() const
{
  return 3.0;
}

Skill* ExoticMeleeSkill::clone()
{
  return new ExoticMeleeSkill(*this);
}

ClassIdentifier ExoticMeleeSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_EXOTIC;
}

// RANGED WEAPON SKILLS

// Thrown Axes
ThrownAxesSkill::ThrownAxesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_AXES;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_AXES_INCREMENT;
}

Skill* ThrownAxesSkill::clone()
{
  return new ThrownAxesSkill(*this);
}

ClassIdentifier ThrownAxesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_AXES;
}

// Thrown Blades
ThrownBladesSkill::ThrownBladesSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLADES;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BLADES_INCREMENT;
}

Skill* ThrownBladesSkill::clone()
{
  return new ThrownBladesSkill(*this);
}

ClassIdentifier ThrownBladesSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_BLADES;
}

// Thrown Bludgeons
ThrownBludgeonsSkill::ThrownBludgeonsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BLUDGEONS_INCREMENT;
}

Skill* ThrownBludgeonsSkill::clone()
{
  return new ThrownBludgeonsSkill(*this);
}

ClassIdentifier ThrownBludgeonsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_BLUDGEONS;
}

// Bows
BowsSkill::BowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_BOWS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_BOWS_INCREMENT;
}

Skill* BowsSkill::clone()
{
  return new BowsSkill(*this);
}

ClassIdentifier BowsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_BOWS;
}

// Crossbows
CrossbowsSkill::CrossbowsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_CROSSBOWS_INCREMENT;
}

Skill* CrossbowsSkill::clone()
{
  return new CrossbowsSkill(*this);
}

ClassIdentifier CrossbowsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_CROSSBOWS;
}

// Daggers
ThrownDaggersSkill::ThrownDaggersSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_DAGGERS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_DAGGERS_INCREMENT;
}

Skill* ThrownDaggersSkill::clone()
{
  return new ThrownDaggersSkill(*this);
}

ClassIdentifier ThrownDaggersSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_DAGGERS;
}

// Rocks
RocksSkill::RocksSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_ROCKS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_ROCKS_INCREMENT;
}

Skill* RocksSkill::clone()
{
  return new RocksSkill(*this);
}

ClassIdentifier RocksSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_ROCKS;
}

// Slings
SlingsSkill::SlingsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SLINGS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_SLINGS_INCREMENT;
}

Skill* SlingsSkill::clone()
{
  return new SlingsSkill(*this);
}

ClassIdentifier SlingsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_SLINGS;
}

// Spears
ThrownSpearsSkill::ThrownSpearsSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_SPEARS;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_SPEARS_INCREMENT;
}

Skill* ThrownSpearsSkill::clone()
{
  return new ThrownSpearsSkill(*this);
}

ClassIdentifier ThrownSpearsSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_SPEARS;
}

// Exotic
ExoticRangedSkill::ExoticRangedSkill()
: RangedWeaponSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_RANGED_EXOTIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_RANGED_EXOTIC_INCREMENT;
}

float ExoticRangedSkill::get_threshold_multiplier() const
{
  return 3.0;
}

Skill* ExoticRangedSkill::clone()
{
  return new ExoticRangedSkill(*this);
}

ClassIdentifier ExoticRangedSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_THROWN_EXOTIC;
}

// MAGIC SKILLS

// Arcane
ArcaneMagicSkill::ArcaneMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_ARCANE;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_ARCANE_INCREMENT;
}

Skill* ArcaneMagicSkill::clone()
{
  return new ArcaneMagicSkill(*this);
}

ClassIdentifier ArcaneMagicSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_ARCANE;
}

// Divine
DivineMagicSkill::DivineMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_DIVINE;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_DIVINE_INCREMENT;
}

Skill* DivineMagicSkill::clone()
{
  return new DivineMagicSkill(*this);
}

ClassIdentifier DivineMagicSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_DIVINE;
}

// Mystic
MysticMagicSkill::MysticMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_MYSTIC_INCREMENT;
}

Skill* MysticMagicSkill::clone()
{
  return new MysticMagicSkill(*this);
}

ClassIdentifier MysticMagicSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_MYSTIC;
}

// Primordial
PrimordialMagicSkill::PrimordialMagicSkill()
: MagicSkill()
{
  skill_name_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL;
  skill_increment_message_sid = SkillTextKeys::SKILL_MAGIC_PRIMORDIAL_INCREMENT;
}

Skill* PrimordialMagicSkill::clone()
{
  return new PrimordialMagicSkill(*this);
}

ClassIdentifier PrimordialMagicSkill::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILL_PRIMORDIAL;
}

// Skills

const int Skills::MAX_SKILL_VALUE = 100;

Skills::Skills()
{
  initialize_skills();
}

Skills::Skills(const Skills& copy_skills)
{
  *this = copy_skills;
}

Skills& Skills::operator=(const Skills& copy_skills)
{
  if (this != &copy_skills)
  {
    this->skills = copy_skills.skills;
  }

  return *this;
}

bool Skills::operator==(const Skills& sk) const
{
  bool result = true;

  result = result && (skills.size() == sk.skills.size());

  if (result)
  {
    SkillMap sk2 = sk.skills;
    SkillMap::const_iterator s_it = skills.begin();
    SkillMap::const_iterator s_it2 = sk2.begin();

    while (s_it != skills.end())
    {
      result = result && (*s_it->second == *s_it2->second);

      if (!result) break;

      s_it++;
      s_it2++;
    }
  }

  return result;
}

void Skills::increment_skills(const Skills& skills_to_increment)
{
  RawSkillMap rsm = skills_to_increment.get_raw_skills();

  for (const auto& skill_pair : rsm)
  {
    SkillType sk = skill_pair.first;
    SkillPtr skill = skill_pair.second;

    if (skill != nullptr)
    {
      unsigned int new_value = static_cast<unsigned int>(get_value(sk) + skill->get_value());
      set_value(sk, new_value);
    }
  }
}

// Set the value of a skill
void Skills::set_value(const SkillType skill_name, const unsigned int value)
{
  SkillPtr skill_to_set = skills[skill_name];
  skill_to_set->set_value(value);
}

// Mark a skill.  JCD FIXME: A skill manager should control this...
void Skills::mark(const SkillType skill_name, const bool override_default)
{
  SkillPtr skill_to_mark = skills[skill_name];

  if (skill_to_mark)
  {
    int value = skill_to_mark->get_value();

    if (value > 0 || skill_to_mark->can_train_from_unlearned() || override_default)
    {
      if (value < MAX_SKILL_VALUE)
      {
        skill_to_mark->get_marks_ref().incr();
      }
    }
  }
}

int Skills::get_value(const SkillType& skill_name) const
{
  int value = -1;
  SkillPtr skill = get_skill(skill_name);

  if (skill != nullptr)
  {
    value = skill->get_value();
  }

  return value;
}

// Get the value and increment the marks, if applicable.
int Skills::get_value_incr_marks(const SkillType& skill_name)
{
  int val = 0;
  SkillPtr skill = get_skill(skill_name);

  if (skill != nullptr)
  {
    val = skill->get_value();

    if (val > 0 || skill->can_train_from_unlearned())
    {
      if (val < MAX_SKILL_VALUE)
      {
        skill->get_marks_ref().incr();
      }
    }
  }

  return val;
}

void Skills::set_skill(const SkillType& st, const SkillPtr skill)
{
  // Always overwrite any previously existing skill.
  skills[st] = skill;
}

void Skills::set_all_to(const int val)
{
  for (auto& s_it : skills)
  {
    SkillPtr cur_skill = s_it.second;

    if (cur_skill != nullptr)
    {
      cur_skill->set_value(val);
    }
  }
}
SkillPtr Skills::get_skill(const SkillType& st) const
{
  SkillPtr result;

  map<SkillType, SkillPtr>::const_iterator sk_it = skills.find(st);

  if (sk_it != skills.end())
  {
    result = sk_it->second;
  }

  return result;
}

bool Skills::has_trainable_skill() const
{
  bool has_ts = false;

  for (const auto& sk_it : skills)
  {
    SkillPtr skill = sk_it.second;

    if (skill != nullptr)
    {
      int val = skill->get_value();
      
      if (val < MAX_SKILL_VALUE && (val > 0 || skill->can_train_from_unlearned()))
      {
        has_ts = true;
        break;
      }
    }
  }

  return has_ts;
}

string Skills::str() const
{
  string skills_str;

  for (SkillMap::const_iterator sk_it = skills.begin(); sk_it != skills.end(); sk_it++)
  {
    SkillPtr skill = sk_it->second;
    skills_str = skills_str + skill->str() + " ";
  }

  return skills_str;
}

bool Skills::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, skills.size());

  for (const RawSkillMap::value_type& skill_pair : skills)
  {
    Serialize::write_enum(stream, skill_pair.first);

    SkillPtr skill = skill_pair.second;

    if (skill)
    {
      Serialize::write_class_id(stream, skill->get_class_identifier());
      skill->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  return true;
}

bool Skills::deserialize(istream& stream)
{
  size_t skills_size = 0;
  Serialize::read_size_t(stream, skills_size);

  skills.clear();

  for (unsigned int i = 0; i < skills_size; i++)
  {
    SkillType skill_type = SkillType::SKILL_GENERAL_ARCHERY;
    Serialize::read_enum(stream, skill_type);

    ClassIdentifier skill_ci = ClassIdentifier::CLASS_ID_NULL;
    Serialize::read_class_id(stream, skill_ci);

    if (skill_ci != ClassIdentifier::CLASS_ID_NULL)
    {
      SkillPtr skill = SkillFactory::create_skill(skill_ci);
      if (!skill) return false;
      if (!skill->deserialize(stream)) return false;

      skills.insert(make_pair(skill_type, skill));
    }
  }

  return true;
}

ClassIdentifier Skills::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SKILLS;
}

// Return a reference to the skills map
std::map<SkillType, SkillPtr>& Skills::get_raw_skills_ref()
{
  return skills;
}

std::map<SkillType, SkillPtr> Skills::get_raw_skills() const
{
  return skills;
}

// Initialize all the general, combat, and magical skills.
void Skills::initialize_skills()
{
  initialize_general_skills();
  initialize_melee_skills();
  initialize_ranged_skills();
  initialize_magic_skills();
}

// Initialize the list of general skills.
void Skills::initialize_general_skills()
{
  std::shared_ptr<ArcherySkill> archery = std::make_shared<ArcherySkill>();
  std::shared_ptr<AwarenessSkill> awareness = std::make_shared<AwarenessSkill>();
  std::shared_ptr<BargainingSkill> bargaining = std::make_shared<BargainingSkill>();
  std::shared_ptr<BeastmasterySkill> beastmastery = std::make_shared<BeastmasterySkill>();
  std::shared_ptr<BlindFightingSkill> blind_fighting = std::make_shared<BlindFightingSkill>();
  std::shared_ptr<BoatingSkill> boating = std::make_shared<BoatingSkill>();
  std::shared_ptr<BowyerSkill> bowyer = std::make_shared<BowyerSkill>();
  std::shared_ptr<BrewingSkill> brewing = std::make_shared<BrewingSkill>();
  std::shared_ptr<CarryingSkill> carrying = std::make_shared<CarryingSkill>();
  std::shared_ptr<CombatSkill> combat = std::make_shared<CombatSkill>();
  std::shared_ptr<CraftingSkill> crafting = std::make_shared<CraftingSkill>();
  std::shared_ptr<DesertLoreSkill> desert_lore = std::make_shared<DesertLoreSkill>();
  std::shared_ptr<DetectionSkill> detection = std::make_shared<DetectionSkill>();
  std::shared_ptr<DisarmTrapsSkill> disarm_traps = std::make_shared<DisarmTrapsSkill>();
  std::shared_ptr<DualWieldSkill> dual_wield = std::make_shared<DualWieldSkill>();
  std::shared_ptr<DungeoneeringSkill> dungeoneering = std::make_shared<DungeoneeringSkill>();
  std::shared_ptr<EscapeSkill> escape = std::make_shared<EscapeSkill>();
  std::shared_ptr<FishingSkill> fishing = std::make_shared<FishingSkill>();
  std::shared_ptr<FletcherySkill> fletchery = std::make_shared<FletcherySkill>();
  std::shared_ptr<ForagingSkill> foraging = std::make_shared<ForagingSkill>();
  std::shared_ptr<ForestLoreSkill> forest_lore = std::make_shared<ForestLoreSkill>();
  std::shared_ptr<HerbalismSkill> herbalism = std::make_shared<HerbalismSkill>();
  std::shared_ptr<HidingSkill> hiding = std::make_shared<HidingSkill>();
  std::shared_ptr<HuntingSkill> hunting = std::make_shared<HuntingSkill>();
  std::shared_ptr<IntimidationSkill> intimidation = std::make_shared<IntimidationSkill>();
  std::shared_ptr<JewelerSkill> jeweler = std::make_shared<JewelerSkill>();
  std::shared_ptr<JumpingSkill> jumping = std::make_shared<JumpingSkill>();
  std::shared_ptr<LeadershipSkill> leadership = std::make_shared<LeadershipSkill>();
  std::shared_ptr<LiteracySkill> literacy = std::make_shared<LiteracySkill>();
  std::shared_ptr<LoreSkill> lore = std::make_shared<LoreSkill>();
  std::shared_ptr<MagicGeneralSkill> magic = std::make_shared<MagicGeneralSkill>();
  std::shared_ptr<MarshLoreSkill> marsh_lore = std::make_shared<MarshLoreSkill>();
  std::shared_ptr<MedicineSkill> medicine = std::make_shared<MedicineSkill>();
  std::shared_ptr<MountainLoreSkill> mountain_lore = std::make_shared<MountainLoreSkill>();
  std::shared_ptr<MountaineeringSkill> mountaineering = std::make_shared<MountaineeringSkill>();
  std::shared_ptr<MusicSkill> music = std::make_shared<MusicSkill>();
  std::shared_ptr<NightSightSkill> night_sight = std::make_shared<NightSightSkill>();
  std::shared_ptr<OceanographySkill> oceanography = std::make_shared<OceanographySkill>();
  std::shared_ptr<PapercraftSkill> papercraft = std::make_shared<PapercraftSkill>();
  std::shared_ptr<ReligionSkill> religion = std::make_shared<ReligionSkill>();
  std::shared_ptr<ScribingSkill> scribing = std::make_shared<ScribingSkill>();
  std::shared_ptr<SkinningSkill> skinning = std::make_shared<SkinningSkill>();
  std::shared_ptr<SmithingSkill> smithing = std::make_shared<SmithingSkill>();
  std::shared_ptr<SpelunkingSkill> spelunking = std::make_shared<SpelunkingSkill>();
  std::shared_ptr<StealthSkill> stealth = std::make_shared<StealthSkill>();
  std::shared_ptr<SwimmingSkill> swimming = std::make_shared<SwimmingSkill>();
  std::shared_ptr<TanningSkill> tanning = std::make_shared<TanningSkill>();
  std::shared_ptr<ThieverySkill> thievery = std::make_shared<ThieverySkill>();
  std::shared_ptr<WandcraftSkill> wandcraft = std::make_shared<WandcraftSkill>();
  std::shared_ptr<WeavingSkill> weaving = std::make_shared<WeavingSkill>();

  skills.insert(make_pair(SkillType::SKILL_GENERAL_ARCHERY, archery));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_AWARENESS, awareness));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BARGAINING, bargaining));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BEASTMASTERY, beastmastery));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BLIND_FIGHTING, blind_fighting));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BOATING, boating));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BOWYER, bowyer));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_BREWING, brewing));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_CARRYING, carrying));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_COMBAT, combat));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_CRAFTING, crafting));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_DESERT_LORE, desert_lore));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_DETECTION, detection));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_DISARM_TRAPS, disarm_traps));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_DUAL_WIELD, dual_wield));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_DUNGEONEERING, dungeoneering));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_ESCAPE, escape));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_FISHING, fishing));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_FLETCHERY, fletchery));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_FORAGING, foraging));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_FOREST_LORE, forest_lore));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_HERBALISM, herbalism));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_HIDING, hiding));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_HUNTING, hunting));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_INTIMIDATION, intimidation));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_JEWELER, jeweler));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_JUMPING, jumping));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_LEADERSHIP, leadership));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_LITERACY, literacy));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_LORE, lore));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MAGIC, magic));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MARSH_LORE, marsh_lore));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MEDICINE, medicine));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MOUNTAIN_LORE, mountain_lore));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MOUNTAINEERING, mountaineering));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_MUSIC, music));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_NIGHT_SIGHT, night_sight));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_OCEANOGRAPHY, oceanography));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_PAPERCRAFT, papercraft));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_RELIGION, religion));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_SCRIBING, scribing));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_SKINNING, skinning));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_SMITHING, smithing));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_SPELUNKING, spelunking));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_STEALTH, stealth));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_SWIMMING, swimming));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_TANNING, tanning));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_THIEVERY, thievery));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_WANDCRAFT, wandcraft));
  skills.insert(make_pair(SkillType::SKILL_GENERAL_WEAVING, weaving));
}

// Initialize all the melee skills.
void Skills::initialize_melee_skills()
{
  std::shared_ptr<AxesSkill> axes = std::make_shared<AxesSkill>();
  std::shared_ptr<ShortBladesSkill> short_blades = std::make_shared<ShortBladesSkill>();
  std::shared_ptr<LongBladesSkill> long_blades = std::make_shared<LongBladesSkill>();
  std::shared_ptr<BludgeonsSkill> bludgeons = std::make_shared<BludgeonsSkill>();
  std::shared_ptr<DaggersSkill> daggers = std::make_shared<DaggersSkill>();
  std::shared_ptr<RodsAndStavesSkill> rods_and_staves = std::make_shared<RodsAndStavesSkill>();
  std::shared_ptr<SpearsSkill> spears = std::make_shared<SpearsSkill>();
  std::shared_ptr<UnarmedSkill> unarmed = std::make_shared<UnarmedSkill>();
  std::shared_ptr<WhipsSkill> whips = std::make_shared<WhipsSkill>();
  std::shared_ptr<ExoticMeleeSkill> exotic = std::make_shared<ExoticMeleeSkill>();

  skills.insert(make_pair(SkillType::SKILL_MELEE_AXES, axes));
  skills.insert(make_pair(SkillType::SKILL_MELEE_SHORT_BLADES, short_blades));
  skills.insert(make_pair(SkillType::SKILL_MELEE_LONG_BLADES, long_blades));
  skills.insert(make_pair(SkillType::SKILL_MELEE_BLUDGEONS, bludgeons));
  skills.insert(make_pair(SkillType::SKILL_MELEE_DAGGERS, daggers));
  skills.insert(make_pair(SkillType::SKILL_MELEE_RODS_AND_STAVES, rods_and_staves));
  skills.insert(make_pair(SkillType::SKILL_MELEE_SPEARS, spears));
  skills.insert(make_pair(SkillType::SKILL_MELEE_UNARMED, unarmed));
  skills.insert(make_pair(SkillType::SKILL_MELEE_WHIPS, whips));
  skills.insert(make_pair(SkillType::SKILL_MELEE_EXOTIC, exotic));
}

// Initialize all the ranged weapon skills.
void Skills::initialize_ranged_skills()
{
  std::shared_ptr<ThrownAxesSkill> axes = std::make_shared<ThrownAxesSkill>();
  std::shared_ptr<ThrownBladesSkill> blades = std::make_shared<ThrownBladesSkill>();
  std::shared_ptr<ThrownBludgeonsSkill> bludgeons = std::make_shared<ThrownBludgeonsSkill>();
  std::shared_ptr<BowsSkill> bows = std::make_shared<BowsSkill>();
  std::shared_ptr<CrossbowsSkill> crossbows = std::make_shared<CrossbowsSkill>();
  std::shared_ptr<ThrownDaggersSkill> daggers = std::make_shared<ThrownDaggersSkill>();
  std::shared_ptr<RocksSkill> rocks = std::make_shared<RocksSkill>();
  std::shared_ptr<SlingsSkill> slings = std::make_shared<SlingsSkill>();
  std::shared_ptr<ThrownSpearsSkill> spears = std::make_shared<ThrownSpearsSkill>();
  std::shared_ptr<ExoticRangedSkill> exotic = std::make_shared<ExoticRangedSkill>();

  skills.insert(make_pair(SkillType::SKILL_RANGED_AXES, axes));
  skills.insert(make_pair(SkillType::SKILL_RANGED_BLADES, blades));
  skills.insert(make_pair(SkillType::SKILL_RANGED_BLUDGEONS, bludgeons));
  skills.insert(make_pair(SkillType::SKILL_RANGED_BOWS, bows));
  skills.insert(make_pair(SkillType::SKILL_RANGED_CROSSBOWS, crossbows));
  skills.insert(make_pair(SkillType::SKILL_RANGED_DAGGERS, daggers));
  skills.insert(make_pair(SkillType::SKILL_RANGED_ROCKS, rocks));
  skills.insert(make_pair(SkillType::SKILL_RANGED_SLINGS, slings));
  skills.insert(make_pair(SkillType::SKILL_RANGED_SPEARS, spears));
  skills.insert(make_pair(SkillType::SKILL_RANGED_EXOTIC, exotic));
}

// Initialize all the magic skills.
void Skills::initialize_magic_skills()
{
  std::shared_ptr<ArcaneMagicSkill> arcane = std::make_shared<ArcaneMagicSkill>();
  std::shared_ptr<DivineMagicSkill> divine = std::make_shared<DivineMagicSkill>();
  std::shared_ptr<MysticMagicSkill> mystic = std::make_shared<MysticMagicSkill>();
  std::shared_ptr<PrimordialMagicSkill> primordial = std::make_shared<PrimordialMagicSkill>();
  std::shared_ptr<CantripsSkill> cantrips = std::make_shared<CantripsSkill>();

  skills.insert(make_pair(SkillType::SKILL_MAGIC_ARCANE, arcane));
  skills.insert(make_pair(SkillType::SKILL_MAGIC_DIVINE, divine));
  skills.insert(make_pair(SkillType::SKILL_MAGIC_MYSTIC, mystic));
  skills.insert(make_pair(SkillType::SKILL_MAGIC_PRIMORDIAL, primordial));
  skills.insert(make_pair(SkillType::SKILL_MAGIC_CANTRIPS, cantrips));
}

#ifdef UNIT_TESTS
#include "unit_tests/Skills_test.cpp"
#endif
