#include "Engine.h"

void NameEntry::Load()
{
    try
    {
        std::ifstream file("resources/data.csv");
        std::string i_buf;
        std::string s_buf;

        while (file.good())
        {
            getline(file, i_buf, ',');
            getline (file, s_buf, ',');

            scoreboard[std::stoi(i_buf)] = s_buf;
        }
        file.close();
    }
    catch (...)
    {
        std::cout << "Can't open score file" << std::endl;
    }
}
void NameEntry::Unload()
{
    try
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            SDL_DestroyTexture(line[i]);
        }
        scoreboard.clear();
    }
    catch (...)
    {
        std::cout << "Can't clear scoreboard textures for reasons; gonna crash instead" << std::endl;
    }
}
void NameEntry::PrintToConsole()
{
    for(std::map<int, std::string>::const_iterator it = scoreboard.begin(); it != scoreboard.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}
void NameEntry::Read(SDL_Renderer* renderer)
{
    int i = 0;
    std::string scorebuf;

    for(std::map<int, std::string>::const_iterator it = scoreboard.begin(); it != scoreboard.end(); it++)
    {
        scorebuf.clear();

        for (unsigned int i = 0; i < 6 - strlen(std::to_string(it->first).c_str()); i++)
            scorebuf.append("0");

        scorebuf.append(std::to_string(it->first).c_str());

        line[i] = TextureFromTextShaded(renderer, scorebuf + "   " + it->second);
        i++;
    }
}
void NameEntry::Write(int nscore, std::string nname)
{
    //Word of advice: DO NOT CALL THIS WHILE THE SCREEN IS SHOWING THE SCOREBOARD

    /* Populating the scoreboard if it is empty */
    if (scoreboard.empty())
    {
        try
        {
            std::ifstream file("resources/data.csv");
            std::string i_buf;
            std::string s_buf;

            while (file.good())
            {
                getline(file, i_buf, ',');
                getline (file, s_buf, ',');

                scoreboard[std::stoi(i_buf)] = s_buf;
            }
            file.close();
        }
        catch (...)
        {
            std::cout << "Can't open score file" << std::endl;
        }
    }

    /* Modifying the scoreboard */

    scoreboard.insert(std::pair<int, std::string>(nscore, nname));

    for (std::map<int, std::string>::const_iterator it = scoreboard.begin(); it != scoreboard.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;

    /* Splitting */

    std::string i_buf[scoreboard.size()];
    std::string s_buf[scoreboard.size()];
    int index = 0;

    for (std::map<int, std::string>::const_iterator it = scoreboard.begin(); it != scoreboard.end(); it++)
    {
        i_buf[index] = std::to_string(it->first);
        s_buf[index] = it->second;


        index++;
    }

    /* Actually writing to file */

    std::ofstream file ("resources/data.csv");

    for (int i = 0; i < 5; i++)
    {
        file << i_buf[i] << "," << s_buf[i];

        if (i != 4)
        {
            file << "," << std::endl;
        }
    }
    file.close();
}

NameEntry::NameEntry()
{
    for (int i = 0; i < 5; i++)
        line[i] = NULL;
}
NameEntry::~NameEntry()
{
    /*for (unsigned int i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(line[i]);
    }
    scoreboard.clear();*/
}

void NoNameEngine::NameEntryLoop()
{
    //PLACEHOLDER
    throw NotImplementedException();
}

