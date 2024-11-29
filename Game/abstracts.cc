#include "abstracts.h"
#include "tile.h"
#include "constants.h"
#include "../Visuals/screen.h"
#include "course.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <sstream>
#include <string>


  
// 4 labs, 4 caffeines, 3 study, 3 tutorial, 4 lecture, 1 netflix
std::vector<Resource> getTileOrder(std::mt19937 *gen) {
    std::vector<Resource> vec{
        Resource::LAB, Resource::LAB, Resource::LAB, Resource::LAB, 
        Resource::CAFF, Resource::CAFF, Resource::CAFF, Resource::CAFF, 
        Resource::LEC, Resource::LEC, Resource::LEC, Resource::LEC, 
        Resource::STD, Resource::STD, Resource::STD, Resource::TUT, 
        Resource::TUT, Resource::TUT, Resource::UM
    };
    std::shuffle(vec.begin(), vec.end(), *gen);
    return vec;
}

std::vector<int> getTileOrder2(std::mt19937 *gen) {
    std::vector<int> vec{2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::shuffle(vec.begin(), vec.end(), *gen);
    return vec;
}

std::shared_ptr<Board> makeBoard(std::string name, std::shared_ptr<Player> players[4], std::mt19937 *gen,
                    std::vector<Resource> tileorder, std::vector<int> tileorder2) {
    std::shared_ptr<Dice> d = std::make_shared<Dice>();
    std::shared_ptr<Goose> g = std::make_shared<Goose>();
    tileorder2.emplace_back(7);

    int t = 0;
    int t2 = 0;
    int goalCount = 0;
    int criteriaCount = 0;
    int tileCount = 0;

    // goals are edges, criterion are corners, tiles are T

    std::vector<std::vector <Tile*>> temp0;
    
    std::vector<std::vector <Criteria*>> tempa;
    
    std::vector <std::vector <Goal*>> tempb;
    std::vector <std::shared_ptr<Tile>> c;
    
   std::vector <std::shared_ptr<Criteria>> a;
    
   std::vector <std::shared_ptr<Goal>> b;
    for (int i = 0; i < BOARD_ROWS; ++i) {
        std::vector <Tile*> temp1;
        std::vector <Criteria*> temp3;
        std::vector <Goal*> temp4;
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
            {
                std::shared_ptr<Criteria> w = std::make_shared<Criteria>();
                w->index = criteriaCount;
                criteriaCount++;
                temp1.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                temp3.emplace_back(w.get());
                a.emplace_back(w);
                break;
            }
            case 'E':
            {
                std::shared_ptr<Goal> s = std::make_shared<Goal>();
                s->index = goalCount;
                goalCount++;
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(s.get());
                b.emplace_back(s);
                break;
            }
            case 'T':
            {
                std::shared_ptr<Tile> q = std::make_shared<Tile>(d.get());
                q->pos = tileCount;
                tileCount++;
                temp1.emplace_back(q.get());
                c.emplace_back(q);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                break;
            }
            
            default:
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                break;
            }
        }
        temp0.emplace_back(temp1);
        tempa.emplace_back(temp3);
        tempb.emplace_back(temp4);

    }
    for (int i = 0; i < BOARD_ROWS; ++i) {
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                if (j + 3 < BOARD_COLUMNS){
                    if (layout.at(i).at(j+3) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i).at(j+3));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if (j - 3 >= 0){
                    if (layout.at(i).at(j-3) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i).at(j-3));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j + 1 < BOARD_COLUMNS) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j+1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i+2).at(j+1));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j + 1 < BOARD_COLUMNS) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j+1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i-2).at(j+1));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j - 1 >= 0) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j-1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i+2).at(j-1));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j - 1 >= 0) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j-1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i-2).at(j-1));
                        v->owner =  tempa.at(i).at(j);
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }

                if (j + 2 < BOARD_COLUMNS){
                    if (layout.at(i).at(j+2) == 'C') {
                        tempa.at(i).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }
                if (j - 2 >= 0){
                    if (layout.at(i).at(j-2) == 'C') {
                        tempa.at(i).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j+2) == 'C') {
                    tempa.at(i-2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }
                if ((j -2 >= 0) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j-2) == 'C') {
                        tempa.at(i-2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j+2) == 'C') {
                        tempa.at(i+2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }
                if ((j - 2 >= 0) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j-2) == 'C') {
                        tempa.at(i+2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                    }
                }

                
                break;
            case 'E':
                for (int k = -1; k < 2; ++k) {
                    if ((j + 1 < BOARD_COLUMNS) && (i + k < BOARD_ROWS) && (i + k >= 0)){
                        if (layout.at(i+k).at(j+1) == 'C') {
                            tempa.at(i+k).at(j+1)->ajacent.emplace_back(tempb.at(i).at(j));
                            tempb.at(i).at(j)->ajacent2.emplace_back(tempa.at(i+k).at(j+1));
                        }
                    }
                    if ((j - 1 >= 0) && (i + k < BOARD_ROWS)&& (i + k >= 0)){
                        if (layout.at(i+k).at(j-1) == 'C') {
                            tempa.at(i+k).at(j-1)->ajacent.emplace_back(tempb.at(i).at(j));
                            tempb.at(i).at(j)->ajacent2.emplace_back(tempa.at(i+k).at(j-1));
                        }
                    }
                }

                if ((j + 2 < BOARD_COLUMNS) && (i + 1 < BOARD_ROWS)){
                    if (layout.at(i+1).at(j+2) == 'E') {
                        tempb.at(i+1).at(j+2)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }
                if ((j - 2 >= 0) && (i + 1 < BOARD_ROWS)){
                    if (layout.at(i+1).at(j-2) == 'E') {
                        tempb.at(i+1).at(j-2)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i - 1 >= 0)){
                    if (layout.at(i-1).at(j+2) == 'E') {
                        tempb.at(i-1).at(j+2)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }
                if ((j - 2 >= 0) && (i - 1 >= 0)){
                    if (layout.at(i-1).at(j-2) == 'E') {
                        tempb.at(i-1).at(j-2)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }
                if (i - 2 >= 0){
                    if (layout.at(i-2).at(j) == 'E') {
                        tempb.at(i-2).at(j)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }
                if (i + 2 < BOARD_ROWS){
                    if (layout.at(i+2).at(j) == 'E') {
                        tempb.at(i+2).at(j)->ajacent1.emplace_back(tempb.at(i).at(j));
                    }
                }

                break;
            case 'T':
                temp0.at(i).at(j)->res = {tileorder.at(t), 1};
                if (tileorder.at(t) != Resource::UM) {
                    temp0.at(i).at(j)->dieVal = tileorder2.at(t2);
                    t2++;
                } else if (tileorder2.at(t2) == 7) {
                    t2++;
                }
                t++;
                break;
            
            default:
                break;
            }
        }
    }
    std::shared_ptr<Board> bor(new Board{name, 0, players[0],players[1],players[2],players[3],std::make_shared<PlayerData>(),std::make_shared<PlayerData>(),std::make_shared<PlayerData>(),std::make_shared<PlayerData>() , b, a, c, d, gen, g});
    for (auto i : bor->data){
        i->b = bor.get();
    }
    return bor;
}

std::shared_ptr<Board> generateBoard(std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen) {
    auto tileorder = getTileOrder(gen);
    auto tileorder2 = getTileOrder2(gen);
    return makeBoard(name, players, gen, tileorder, tileorder2);
}

std::shared_ptr<Board> loadBoard(std::string info, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen) {
    std::istringstream iss{info};
    std::vector<Resource> tileorder;
    std::vector<int> tileorder2;
    int cur;

    int i = 0;
    while (iss >> cur) {
        if (i % 2) {
            tileorder2.emplace_back(cur);
        } else {
            tileorder.emplace_back(static_cast<Resource>(cur));
        }
        ++i;
    }
    return makeBoard(name, players, gen, tileorder, tileorder2);
}

std::shared_ptr<Board> openFile(std::string filename, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen) {
   std::ifstream file(filename);
    if (!file.is_open()) {        
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::ostringstream ss;       
    ss << file.rdbuf();           
    return loadGameState(ss.str(), name, players, gen);
}

std::shared_ptr<Board> loadGameState(std::string info, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen) {
    std::istringstream iss{info};
    std::string s;
    int turn;
    int goose;
    int numCaf = 0, numLab = 0, numLec = 0, numStd = 0, numTut = 0;
    std::vector<std::string> playerLines;
    std::string boardLine;
    char oof;
    std::vector<std::string> lins;
    std::string lin;
    std::shared_ptr<Board> b;
    while (std::getline(iss, lin)) {
        if (lin.size() > 0) {
            lins.emplace_back(lin);
        }
    }

    if (lins.size() == 7) {
        turn = std::stoi(lins.at(0));

        for (int i = 1; i < 5; ++i) {
            playerLines.emplace_back(lins.at(i));     
        }

        // initialize board with board data
        b = loadBoard(lins.at(5), name, players, gen);
        b->turn = turn;
        

        // for each player, read in 5 ints, then g, then as many ints until c, then as many pairs as possible
        for (int i = 0; i < 4; ++i) {
            std::istringstream playerStream{playerLines.at(i)};
            playerStream >> numCaf >> numLab >> numLec >> numStd >> numTut;
            for (int i = 0; i < numCaf; ++i) {
                hadd(b->data[i]->hand.get(), Resource::CAFF);
            }
            for (int j = 0; j < numLab; ++j) {
                hadd(b->data[i]->hand.get(), Resource::LAB);
            }
            for (int j = 0; j < numLec; ++j) {
                hadd(b->data[i]->hand.get(), Resource::LEC);
            }
            for (int j = 0; j < numStd; ++j) {
                hadd(b->data[i]->hand.get(), Resource::STD);
            }
            for (int j = 0; j < numTut; ++j) {
                hadd(b->data[i]->hand.get(), Resource::TUT);
            }

            playerStream >> oof; // reads 'g'

            int n;
            int m;
            char nextChar = playerStream.peek();
            if (nextChar != 'c') {
                while (playerStream >> n) {
                    b->goals.at(n)->buy_start(b->data[i].get());
                }
                playerStream.clear();
                playerStream.ignore();
                    while (playerStream >> n >> m) {
                        b->criterions.at(n)->force_buy(b->data[i].get());
                        b->criterions.at(n)->setgreed(m);
                        b->data[i]->points = b->data[i]->points + m - 1;
                        b->criterions.at(n)->cost = b->criterions.at(n)->COSTS[m-1];
                    }
            } else {
                    playerStream >> oof;
                  while (playerStream >> n >> m) {
                        b->criterions.at(n)->force_buy(b->data[i].get());
                        b->criterions.at(n)->setgreed(m);
                        b->data[i]->points = b->data[i]->points + m - 1;
                        b->criterions.at(n)->cost = b->criterions.at(n)->COSTS[m-1];
                    }
            }
        }
        goose = stoi(lins.at(6));
        if (goose >= 0) {
            b->goose->move(b->tiles.at(goose).get());
        }
    } else if (lins.size() == 1) {
        b = loadBoard(lins.at(0), name, players, gen);
    }
    // get string sequences for each player
    return b;
}

std::ostream& operator<<(std::ostream &os, const PlayerData& player) {
    os << player.getAmountResource(Resource::CAFF) << " "
       << player.getAmountResource(Resource::LAB) << " "
       << player.getAmountResource(Resource::LEC) << " "
       << player.getAmountResource(Resource::STD) << " "
       << player.getAmountResource(Resource::TUT) << " ";
    os << "g" << " ";
    for (const auto& edge : player.edges) {
        if (edge) {
            os << edge->index << " ";
        }
    }
    os << "c" << " ";
    for (const auto& corner : player.corners) {
        if (corner) {
            os << corner->index << " " << corner->getgreed() << " ";
        }
    }
    os << std::endl;
    return os;
}

void Board::saveBoard(std::string filename, controller* cont) {
    *cont << controller::Commands::SAVEBOARD;
    std::ofstream file{filename};

    file << turn << std::endl;
    for (const auto& playerD : data) {
        file << *playerD;
    }
    for (const auto& tile : tiles) {
        if (tile->dieVal == -1) {
            file << static_cast<int>(tile->res.prod) << " " << 7 << " ";
        } else {
            file << static_cast<int>(tile->res.prod) << " " << tile->dieVal << " ";
        }
    }
    file << std::endl;
    if (goose->tile) {
        file << goose->tile->pos << std::endl;
    } else {
        file << "-1" << std::endl;
    }
}

int PlayerData::getAmountResource(Resource r) const {
    int count = 0;
    for (const auto& card : hand->cards) {
        if (card == r) {
            ++count;
        }
    }
    return count;
}


void Goose::move(Tile* target){
    if (tile) {
        tile->goosed = false;
    }
    if (target) {
        target->goosed = true;
    }
    tile = target;
}


void PlayerData::gain(Hand h){
    if (h.cards.at(0) != Resource::UM) {
        for (Resource i : h.cards) {
            hadd(hand.get(), i);
        }
    } else {
        can_steal = true;
    }
}

Tile* PlayerData::selectTargetTile(controller* cont) {
    int targetIndex = -1;

    // Input loop to ensure a valid number between 0 and 18 is selected
    while (true) {
        *cont << controller::Commands::MOVEG;
        *cont >> targetIndex;

        // Check if input is valid
        if (targetIndex < 0 || targetIndex > 18) {
            *cont << controller::Commands::INVALIDNUM;
        } else {
            break; // Valid input
        }
    }

    // Assuming `b->tiles` is a vector of tiles, and targetIndex corresponds to its index
    if (targetIndex >= 0 && targetIndex < int(b->tiles.size())) {
        return b->tiles.at(targetIndex).get(); // Return the selected tile
    }

    *cont << 0;
    return nullptr; // In case of an invalid index (edge case)
}

PlayerData* PlayerData::selectPlayerToStealFrom(const std::vector<PlayerData*>& options, controller* cont) {
    if (options.empty()) {
        *cont << controller::Commands::NOPLAY;
        return nullptr;
    }

    *cont << controller::Commands::STEAL;

    // Display the list of available options
    Player* pl[3]{nullptr,nullptr, nullptr};
    for (size_t i = 0; i < options.size(); ++i) {
        pl[i] = b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [options, i](const std::shared_ptr<PlayerData>& p) {return p.get() == options[i];}))].get();
    }
    cont->chooseplayer(const_cast<const Player**>(pl));
    int selectedIndex = -1;

    // Input loop to ensure valid selection
    while (true) {
        *cont >> selectedIndex;

        if (selectedIndex < 0 || selectedIndex >= static_cast<int>(options.size())) {
            *cont << controller::Commands::INVALIDPLAYER;
        } else {
            break; // Valid input
        }
    }

    // Return the selected player
    return options[selectedIndex];
}

void PlayerData::goosefy(controller* cont){
    for (std::shared_ptr<PlayerData> p : b->data) {
        p->Discard();
    }
    Tile* target = selectTargetTile(cont);
    if (target) {
        b->goose->move(target);
        std::vector <PlayerData*> options;
        stealify(b);
        for (std::shared_ptr<PlayerData> i : b->data) {
            if ((i->can_steal) && (i.get() != this)){
                options.emplace_back(i.get());
            }
        }
        PlayerData* selected = selectPlayerToStealFrom(options, cont);
        if (selected){
            if (selected->hand->cards.size()){
                std::shuffle(selected->hand->cards.begin(), selected->hand->cards.end(), *b->gen);
                hadd(hand.get(), selected->hand->cards.front());
                hsub(selected->hand.get(), selected->hand->cards.front());
            }
        }
    }

}

void PlayerData::Discard(){
    if (int(hand->cards.size()) >= 10) {
        std::shuffle(hand->cards.begin(), hand->cards.end(), *b->gen);
        for (int i = int(hand->cards.size())/2; i > 0; i--) {
            hsub(hand.get(), hand->cards.front());
        }
    }

};

void PlayerData::roll(Dice* d, controller* cont){
    if (!loaded_dice) {
    std::uniform_int_distribution<> dist(1, 6);
    int num = dist(*b->gen);
    int num2 = dist(*b->gen);
    for (std::shared_ptr<PlayerData> i : b->data) {
        i->can_steal = false;
    } 
    d->setValue(num+num2, this, cont);
    }
    else {
        int val;
        while (true) {
        *cont << controller::Commands::PICK;
        *cont >> val;
        // Check if input is valid
        if (val < 0 || val > 12) {
            *cont << controller::Commands::INVALIDNUM;
        } else {
            break; // Valid input
        }
    }
    d->setValue(val, this, cont);
    }
}


void PlayerData::turn(controller* cont) {
    bool turnActive = true;
    bool rol = false;
    std::string saveFile;

    // Start the player's turn by rolling the dice
    Player *play = b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [this](const std::shared_ptr<PlayerData>& p) {return p.get() == this;}))].get();

    cont->board(*b);
    cont->turn(*play, b->turn);
    *cont << controller::Commands::MENU;
    Action act;
    while (turnActive) {

        
        *cont >> act;

        switch (act) {
            case Action::TRADE: {
                if (rol) {
                    Trade(cont);
                } else {
                    *cont << controller::Commands::MUST;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::ROLL: {
                if (!rol){
                    roll(b->dice.get(), cont);
                    rol = true;
                } else {
                    *cont << controller::Commands::ALRROLL;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::CRIT: {
                if (rol) {
                *cont << controller::Commands::CHOOSECRIT;
                int index;
                *cont >> index;
                if (index >= 0 && index < int(b->criterions.size())) {
                    if (b->criterions[index]->buy(this)) {
                        // idk, maybe update screen?
                    } else {
                        *cont << controller::Commands::INVALIDCRIT;
                    }
                } else {
                    *cont << controller::Commands::INVALIDNUM;
                }
            } else {
                    *cont << controller::Commands::MUST;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::GOAL: {
                if (rol) {
                *cont << controller::Commands::CHOOSEGOAL;
                int index;
                *cont >> index;
                if (index >= 0 && index < int(b->goals.size())) {
                    if (b->goals[index]->buy(this)) {
                        // idk, maybe update screen?
                    } else {
                        *cont << controller::Commands::INVALIDGOAL;
                    }
                } else {
                    *cont << controller::Commands::INVALIDNUM;
                }
                } else {
                    *cont << controller::Commands::MUST;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::BOARD: {
                cont->board(*b);
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::SAVE: {
                if (rol){
                    *cont << controller::Commands::SFILENAME; // "enter filename:"
                    *cont >> saveFile;
                    b->saveBoard(saveFile, cont);
                } else {
                    *cont << controller::Commands::MUST;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::END: {
                if (rol) {
                    turnActive = false;
                } else {
                    *cont << controller::Commands::MUST;
                }
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::STATUS: {
                *cont << controller::Commands::VIEWSTATUS;
                int index;
                *cont >> index;
                if (index >= 0 && index < 4) {
                    cont->printstatus(*(b->data[index]));
                }
                break;
            }
            case Action::COMPLETIONS: {
                *cont << controller::Commands::VIEWCOMP;
                int index;
                *cont >> index;
                if (index >= 0 && index < 4) {
                    cont->printcompletions(*(b->data[index]));
                }
                break;
            }
            case Action::SWITCH: {
                loaded_dice = !loaded_dice;
                *cont << controller::Commands::MENU;
                break;
            }
            case Action::EXIT: {
                throw std::runtime_error("Turn Done");
                break;
            }
            default:
                *cont << controller::Commands::MENU;
        }
    }
}

void firstTurn(Board* b, controller* cont) {
    for (int i = 0; i < 4; ++i) {
         cont->board(*b);
        PlayerData* player = b->data[i].get();
        Player* play = b->players[i].get();
        
        cont->turn(*play, 0);

        // Player selects a criteria
        Criteria* chosenCriteria = nullptr;
        while (!chosenCriteria) {
            for (size_t j = 0; j < b->criterions.size(); ++j) {
                if ((!b->criterions[j]->owner) && std::all_of(b->criterions[j]->neighbours.begin(), b->criterions[j]->neighbours.end(), [](Criteria* i){return !(i->owner);})){
                    //idk maybe graphic?
                }
            }

            *cont << controller::Commands::CHOOSECRIT;
            int criteriaIndex;
            *cont >> criteriaIndex;

            if (criteriaIndex >= 0 && criteriaIndex < int(b->criterions.size()) && !b->criterions[criteriaIndex]->owner && std::all_of(b->criterions[criteriaIndex]->neighbours.begin(), b->criterions[criteriaIndex]->neighbours.end(), [](Criteria* i){return !(i->owner);})) {
                chosenCriteria = b->criterions[criteriaIndex].get();
            } else {
                 *cont << controller::Commands::INVALIDNUM;
            }
        }

        // Display adjacent goals for the selected criteria
        std::vector<Goal*> adjacentGoals;
        for (Goal* goal : chosenCriteria->ajacent) {
                adjacentGoals.push_back(goal);
        }

        if (adjacentGoals.empty()) {
            *cont << controller::Commands::INVALIDNUM;
            --i; 
            continue;
        }


        Goal* chosenGoal = nullptr;
        while (!chosenGoal) {
            for (size_t j = 0; j < adjacentGoals.size(); ++j) {
                // graph
            }

            *cont << controller::Commands::CHOOSEGOAL;
            int goalIndex;
            *cont >> goalIndex;

            if (goalIndex >= 0 && goalIndex < int(b->goals.size())) {
                if (std::count(adjacentGoals.begin(), adjacentGoals.end(), b->goals.at(goalIndex).get()) > 0) {
                chosenGoal = b->goals.at(goalIndex).get();
                } else {
                    *cont << controller::Commands::INVALIDGOAL;
                }
            } else {
                *cont << controller::Commands::INVALIDNUM;
            }
        }

        // Mark the criteria and goal as bought and assign them to the player
        if (chosenCriteria && chosenGoal) {
            chosenCriteria->buy_start(player);
            chosenGoal->buy_start(player);
            //graph
        }
    }
}

void PlayerData::writedata(){

}

void PlayerData::Trade(controller* cont) {
    // Prompt the player to create an offer by selecting cards to give and receive
    *cont << controller::Commands::TRADE1;
    *cont << *hand;
    // Implement card selection logic (select cards to give)
    ResourceCollection temp1;
    temp1.inputResources(cont);
    std::unique_ptr<Hand> selectedHand1 = std::make_unique<Hand>(temp1.get_hand());
    *cont << controller::Commands::TRADE2;
    ResourceCollection temp2;
    temp2.inputResources(cont);
    std::unique_ptr<Hand> selectedHand2 = std::make_unique<Hand>(temp2.get_hand());
    *cont << *selectedHand1;
    *cont << *selectedHand2;
    // Implement card selection logic (select cards to receive)

    // Check if the player has enough resources for the trade
    Hand* sh1 =selectedHand1.get();
    if (std::all_of(selectedHand1->cards.begin(), selectedHand1->cards.end(), [this, sh1](Resource i) {
            return herr(hand.get(), i) >= herr(sh1, i);
        })) {

        int selectedPlayeri = 0;

        while (true) {
        *cont << controller::Commands::TRADE3;
        *cont >> selectedPlayeri;

        if (selectedPlayeri < 0 || selectedPlayeri >= 4) {
            *cont << controller::Commands::INVALIDNUM;
        } else {
            break; // Valid input
        }
        }
        PlayerData* selectedPlayer = b->data[selectedPlayeri].get();


        if (selectedPlayer != this) {
            std::string response;
            cont->accept(b->players[selectedPlayeri].get());
            *cont >> response;
            if (response == "y" && selectedPlayer->hasResourcesForTrade(selectedHand2.get())) {
                // Execute the trade if the player accepts
                executeTrade(selectedPlayer, selectedHand1.get(), selectedHand2.get());
                return;  // End trade once successful
            }
        }
    }
    *cont << controller::Commands::INVTRADE;
}

// Helper function to check if the player has enough resources for the trade
bool PlayerData::hasResourcesForTrade(const Hand* selectedHand) {
    Hand h = *selectedHand;
    for (auto& card : selectedHand->cards) {
        if (herr(hand.get(), card) < herr(&h, card)) {  // Not enough of the selected card
            return false;
        }
    }
    return true;
}

// Helper function to execute the trade (exchange cards between players)
void PlayerData::executeTrade(PlayerData* selectedPlayer, Hand* hand1, Hand* hand2) {
    // Transfer cards from current player to the selected player
    for (auto& card : hand1->cards) {
        hadd(selectedPlayer->hand.get(), card);  // Add card to the selected player
        hsub(hand.get(), card);  // Remove card from the current player's hand
    }
    // Transfer cards from selected player to current player
    for (auto& card : hand2->cards) {
        hsub(selectedPlayer->hand.get(), card);  // Remove card from the selected player
        hadd(hand.get(), card);  // Add card to the current player's hand
    }
}
void run_turn (Board* b, controller* cont) {
    b->turn++;
    b->data[(b->turn-1)%4]->turn(cont);
}

PlayerData::~PlayerData(){
    // corners.clear();
    // edges.clear();
    // eyes.clear();
    // hand.reset();

}

void stealify(Board* b){
    for (auto p : b->data){
        for (auto e : p->eyes) {
            for (auto c: e->subject->eyes){
                if (c->subject->goosed) {
                    p->can_steal = true;
                }
            }
        }
    }
}
Board::~Board() {

}

Goose::~Goose(){
    // tile = nullptr;
}

void PlayerData::detach(Observer* o){
    if (eyes.size()) {
    for (auto it = eyes.begin(); it != eyes.end(); ++it) {
        if ((*it).get() == o) {
            eyes.erase(it);
            break;
        }
    }
    }
}
void PlayerData::detach(Goal* o){
    // if (edges.size()) {
    // for (auto it = edges.begin(); it != edges.end(); ++it) {
    //     if ((*it) == o) {
    //         edges.erase(it);
    //          break;
    //     }
    // }
    // }
}
void PlayerData::detach(Criteria* o){
    // if (corners.size()) {
    // for (auto it = corners.begin(); it != corners.end(); ++it) {
    //     if ((*it) == o) {
    //         corners.erase(it);
    //         break;
    //     }
    // }
    // }
}


