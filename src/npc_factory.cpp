#include "../include/npc_factory.h"
#include "../include/npc.h"
#include <fstream>
#include <string>
#include <regex>

int NpcFactory::get_position_x(void)
{
    return rng.get_int(0, size_x - 1);
}

int NpcFactory::get_position_y(void)
{
    return rng.get_int(0, size_y - 1);
}

std::string NpcFactory::get_uname(std::string base_name)
{
    return base_name + "-" + std::to_string(++counter[NpcType::elf]);
}

NpcFactory::NpcFactory()
    : NpcFactory(25, 25) {}

NpcFactory::NpcFactory(int size_x, int size_y)
    : size_x(size_x), size_y(size_y), counter{0, 0, 0} {}

std::shared_ptr<BaseNPC> NpcFactory::create_npc(void)
{
    NpcType npc_type = static_cast<NpcType>(rng.get_int(0, 2));
    return create_npc(npc_type);
}

std::shared_ptr<BaseNPC> NpcFactory::create_npc(const NpcType& npc_type)
{
    switch (npc_type) {
    case NpcType::elf:
        return std::make_shared<Elf>(
            get_uname("Elf"),
            get_position_x(),
            get_position_y()
        );

    case NpcType::knight:
        return std::make_shared<Knight>(
            get_uname("Knight"),
            get_position_x(),
            get_position_y()
        );

    case NpcType::rogue:
        return std::make_shared<Rogue>(
            get_uname("Rogue"),
            get_position_x(),
            get_position_y()
        );
    default:
        throw std::invalid_argument("Unknown NPC type");
    }
}

void NpcFactory::save_to_file(std::vector<std::shared_ptr<BaseNPC>>& npcs, std::string& filename)
{
    std::ofstream file(filename);

    for (const auto& npc : npcs)
        file << *npc << '\n';

    file.close();
}

std::vector<std::shared_ptr<BaseNPC>> NpcFactory::load_from_file(std::string& filename)
{
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    std::ifstream file(filename);
    std::string line;

    std::regex pattern(R"(\[(\w+)\] '([\w-]+)' at \((\d+), (\d+)\))");
    std::smatch matches;

    while (std::getline(file, line))
    {
        if (std::regex_match(line, matches, pattern))
        {
            std::string npc_type_str = matches[1];
            std::string name = matches[2];
            int x = std::stoi(matches[3]);
            int y = std::stoi(matches[4]);

            if (npc_type_str == "Elf")
            {
                npcs.push_back(std::make_shared<Elf>(name, x, y));
                ++counter[NpcType::elf];
            }
            else if (npc_type_str == "Knight")
            {
                npcs.push_back(std::make_shared<Knight>(name, x, y));
                ++counter[NpcType::knight];
            }
            else if (npc_type_str == "Rogue")
            {
                npcs.push_back(std::make_shared<Rogue>(name, x, y));
                ++counter[NpcType::rogue];
            }
        }
    }

    file.close();

    return npcs;
}