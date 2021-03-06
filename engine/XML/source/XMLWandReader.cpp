#include "XMLWandReader.hpp"

XMLWandReader::XMLWandReader()
{
}

XMLWandReader::~XMLWandReader()
{
}

// Methods for reading in Wand details from an XML node conformant to the Wand type.
void XMLWandReader::parse(WandPtr wand, GenerationValues& gv, const XMLNode& wand_node, const bool force_ascii)
{
  if (!wand_node.is_null())
  {
    XMLItemReader::parse(wand, gv, wand_node, force_ascii);
    
    EffectType effect_type  = static_cast<EffectType>(XMLUtils::get_child_node_int_value(wand_node, "Effect", static_cast<int>(EffectType::EFFECT_TYPE_NULL)));
    wand->set_effect_type(effect_type);

    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(wand_node, "Damage");
    if (!damage_node.is_null())
    {
      Damage d;
      parse_damage(d, damage_node);

      wand->set_has_damage(true);
      wand->set_damage(d);
    }

    uint range = XMLUtils::get_child_node_int_value(wand_node, "Range");
    wand->set_range(range);

    uint radius = XMLUtils::get_child_node_int_value(wand_node, "Radius", wand->get_radius());
    wand->set_radius(radius);

    SpellShapeType spell_shape = static_cast<SpellShapeType>(XMLUtils::get_child_node_int_value(wand_node, "BeamType", static_cast<int>(SpellShapeType::SPELL_SHAPE_BEAM)));
    wand->set_spell_shape_type(spell_shape);

    Colour spell_colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(wand_node, "Colour", static_cast<int>(Colour::COLOUR_WHITE)));
    wand->set_spell_colour(spell_colour);
  }
}

