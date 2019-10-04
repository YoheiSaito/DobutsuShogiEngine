#include "position.hpp"
#include "move_definition.hpp"

namespace AnimalEngine{

Position& Position::operator=(const Position& p){
    this->chickin  = p.chickin;
    this->lion     = p.lion;
    this->giraffe  = p.giraffe;
    this->elephant = p.elephant;
    return *this;
};


std::vector<Position> Position::gen_move(Turn turn){
    std::vector<Position> poses;
    auto board = make_map();
    bool ela = elephantA_owner, gra = giraffeA_owner;
    bool lra =     lionA_owner, cra = chickinA_owner;
    bool elb = elephantA_owner, grb = giraffeA_owner;
    bool lrb =     lionA_owner, crb = chickinA_owner;
    std::unordered_map<char,uint8_t> owner_a = {
        {'e', ela}, {'g', gra}, {'l', lra}, {'C', cra}, {'h', cra},
        {'E', ela}, {'G', gra}, {'L', lra}, {'c', cra}, {'H', cra},
    };
    std::unordered_map<char,uint8_t> owner_b = {
        {'e', elb}, {'g', grb}, {'l', lrb}, {'C', crb}, {'h', crb},
        {'E', elb}, {'G', grb}, {'L', lrb}, {'c', crb}, {'H', crb},
    };
    std::unordered_map<char, PositionSeperator> mp_rf= {
        {'e', elephant}, {'g', giraffe}, {'l', lion},
        {'E', elephant}, {'G', giraffe}, {'L', lion},
        {'C',  chickin}, {'h', chickin},
        {'c',  chickin}, {'H', chickin}, 
    };


    auto putted = std::get<0>(board);
    auto having = turn ? std::get<1>(board): std::get<2>(board);
    // put
    for(size_t h = 0; h < having.size(); h+=2){
        { // koma a
            size_t j = h;
            auto&& p = having[j];
            if( p != ' ' ){
                for(int i = 0; i < OB; i++){
                    if(putted[i] ==' ' && mp_rf[p].a_pos >= OB){
                        auto tmp = mp_rf[p].a_pos;
                        mp_rf[p].a_pos = i;
                        poses.push_back(*this);
                        mp_rf[p].a_pos = tmp;
                    }
                }
            }
            continue;
        }{ // koma b
            size_t j = h+1;
            auto&& p = having[j];
            if( p != ' ' ){
                for(int i = 0; i < OB; i++){
                    if(putted[i] ==' ' && mp_rf[p].b_pos >= OB){
                        auto tmp = mp_rf[p].b_pos;
                        mp_rf[p].b_pos = i;
                        poses.push_back(*this);
                        mp_rf[p].b_pos = tmp;
                    }
                }
            } 
        }
    }

    for(uint8_t i = 0; i < OB; i++){
        char& p = putted[i];
        if( p == ' ' ) continue;
        if( turn == BLACK && std::islower(p) ){
            std::vector<uint8_t> v = move_definition[p][i];
            for(auto&& dst : v){

                if( !std::islower(putted[dst]) ){
                   Position p = this->move({i, dst}, turn, board);
                    poses.push_back(p);
                }
            }
        }
        else if( turn == WHITE && std::isupper(p) ){
            std::vector<uint8_t> v = move_definition[p][i];
            for(auto&& dst : v){
                if( !std::islower(putted[dst]) ){
                    Position p = this->move({i, dst}, turn, board);
                    poses.push_back(p);
                }
            }
        }
    }

    // move
    return poses;
}
Position Position::move(Move mv, Turn turn, const boost::optional<BoardMap> mp){
    BoardMap bm = mp ? mp.get():  make_map();
    Position p = *this;
    auto board = std::get<0>(bm);
    switch(board[mv.dst]){
        case 'H':
        case 'h':
        case 'C':
        case 'c':
            if( p.chickin.a_pos == mv.dst ){
                p.chickinA_owner = turn;
                p.chickin.a_pos = OB_CHICKIN;
            }else if( p.chickin.b_pos == mv.dst ){
                p.chickinB_owner = turn;
                p.chickin.b_pos = OB_CHICKIN;
            }
            break;
        case 'L':
        case 'l':
            if( p.lion.a_pos == mv.dst ){
                p.lionA_owner = turn;
                p.lion.a_pos = OB_LION;
            }else if( p.lion.b_pos == mv.dst ){
                p.lionB_owner = turn;
                p.lion.b_pos = OB_LION;
            }
            break;
        case 'E':
        case 'e':
            if( p.elephant.a_pos == mv.dst ){
                p.elephantA_owner = turn;
                p.elephant.a_pos = OB_ELEPHANT;
            }else if( p.elephant.b_pos == mv.dst ){
                p.elephantB_owner = turn;
                p.elephant.b_pos = OB_ELEPHANT;
            }

            break;
        case 'g':
        case 'G':
            if( p.giraffe.a_pos == mv.dst ){
                p.giraffeA_owner = turn;
                p.giraffe.a_pos = OB_GIRAFFE;
            }else if( p.giraffe.b_pos == mv.dst ){
                p.giraffeB_owner = turn;
                p.giraffe.b_pos = OB_GIRAFFE;
            }
            break;
        case ' ':
        default:
            break;
    }
    switch(board[mv.src]){
        case 'H':
        case 'h':
        case 'C':
        case 'c':
            if( p.chickin.a_pos == mv.src )
                p.chickin.a_pos = mv.dst;
            if( p.chickin.b_pos == mv.src )
                p.chickin.b_pos = mv.dst;
            break;
        case 'L':
        case 'l':
            if( p.lion.a_pos == mv.src )
                p.lion.a_pos = mv.dst;
            if( p.lion.b_pos == mv.src )
                p.lion.b_pos = mv.dst;
            break;
        case 'E':
        case 'e':
            if( p.elephant.a_pos == mv.src )
                p.elephant.a_pos = mv.dst;
            if( p.elephant.b_pos == mv.src )
                p.elephant.b_pos = mv.dst;
            break;
        case 'g':
        case 'G':
            if( p.giraffe.a_pos == mv.src )
                p.giraffe.a_pos = mv.dst;
            if( p.giraffe.b_pos == mv.src )
                p.giraffe.b_pos = mv.dst;
            break;
        case ' ':
        default:
            break;
    }
    return p;
}

bool Position::operator==(const Position& p){
    bool ret = this->owner == p.owner;
    ret &= this->chickin_promote == p.chickin_promote;
    ret &= this->chickin.all  == p.chickin.all;
    ret &= this->lion.all     == p.lion.all;
    ret &= this->giraffe.all  == p.giraffe.all;
    ret &= this->elephant.all == p.elephant.all;
    return ret;
}
std::string Position::operator()(){ 
    auto bt = make_map();
    std::string board(std::get<0>(bt).begin(),std::get<0>(bt).end());
    std::string black(std::get<1>(bt).begin(),std::get<1>(bt).end());
    std::string white(std::get<2>(bt).begin(),std::get<2>(bt).end());
    std::stringstream ss;
    ss << "-------------\n";
    ss << white << '\n';
    ss << "-------------\n";
    for(size_t i = 0; i < board.size(); i+=3){
        ss << "-------------\n";
        char s[14]="";
        std::sprintf(s, "| %c | %c | %c |\n", board[i],board[i+1],board[i+2]);
        ss << s;
    }
    ss << "-------------\n";
    ss << "-------------\n";
    ss << black << '\n';
    ss << "-------------\n";
    return ss.str();
}


bool Position::is_tsumi(Turn turn) {
    if(lionA_owner != turn && lionB_owner != turn)
        return true;
    if(lionB_owner != turn && lion.b_pos >= OB)
        return true;
    if(lionA_owner != turn && lion.a_pos >= OB)
        return true;
    //tri
    auto tryIndex = turn != BLACK ? PositionIndex::B1 : PositionIndex::B4;
    if(lionA_owner != turn && lion.a_pos == tryIndex)
        return true;
    if(lionB_owner != turn && lion.b_pos == tryIndex)
        return true;
    return false;
}


/* return is boardstr black_mochigoma white_mochigoma*/
/* order of return value is hiyoko-zou-kirin-lion*/ 
BoardMap Position::make_map(){
    StArray<12> board;
    StArray<8>  black;
    StArray<8>  white;
    for(auto&& c : board) c = ' ';
    for(auto&& c : black) c = ' ';
    for(auto&& c : white) c = ' ';

    char cb = chickinA_promote ? 'h':'c';
    char cw = chickinA_promote ? 'H':'C';

    char cc = elephantA_owner == Turn::BLACK? cb:cw;
    if(chickin.a_pos < OB)
        board[chickin.a_pos] = cc;
    else {
        if(chickinA_owner == BLACK)
            black[0] = 'c';
        else 
            white[0] = 'C';
    }

    cc = chickinB_owner == Turn::BLACK? cb:cw;
    if(chickin.b_pos < OB)
        board[chickin.b_pos] = cc;
    else{
        if(chickinB_owner == BLACK)
            black[1] = 'c';
        else 
            white[1] = 'C';
    }

    char ce = elephantA_owner == Turn::BLACK?'e':'E';
    if(elephant.a_pos < OB)
        board[elephant.a_pos] = ce;
    else 
        (elephantA_owner == BLACK?black[2]:white[2]) = ce;
    ce = elephantB_owner == Turn::BLACK?'e':'E';
    if(elephant.b_pos < OB)
        board[elephant.b_pos] = ce;
    else
        (elephantB_owner == BLACK?black[3]:white[3]) = ce;

    char cg = giraffeA_owner == Turn::BLACK?'g':'G';
    if(giraffe.a_pos < OB)
        board[giraffe.a_pos] = cg;
    else 
        (giraffeA_owner == BLACK?black[4]:white[4]) = cg;
    cg = giraffeB_owner == Turn::BLACK?'g':'G';
    if(giraffe.b_pos < OB)
        board[giraffe.b_pos] = cg;
    else
        (giraffeB_owner == BLACK?black[5]:white[5]) = cg;

    char cl = lionA_owner == Turn::BLACK?'l':'L';
    if(lion.a_pos < OB)
        board[lion.a_pos] =  cl;
    else 
        (lionA_owner == BLACK?black[6]:white[6]) = cl;
    cl = lionB_owner == Turn::BLACK?'l':'L';
    if(lion.b_pos < OB)
        board[lion.b_pos] =  cl;
    else 
        (lionB_owner == BLACK?black[7]:white[7]) = cl;

    return std::make_tuple(board, black, white);
}


void Position::set_chickinA_pos (PositionIndex p, Owner owner, boost::optional<bool> promote){
    this->chickin.a_pos = p;
    this->chickinA_owner = owner;
    if(promote)
        chickinA_promote = promote.get();
}
void Position::set_chickinB_pos (PositionIndex p, Owner owner, boost::optional<bool> promote){
    this->chickin.b_pos = p;
    this->chickinB_owner = owner;
    if(promote)
        chickinB_promote = promote.get();
}

void Position::set_lionA_pos (PositionIndex p, Owner owner){
    this->lion.a_pos = p;
    this->lionA_owner = owner;
}
void Position::set_lionB_pos (PositionIndex p, Owner owner){
    this->lion.b_pos = p;
    this->lionB_owner = owner;
}
void Position::set_elephantA_pos (PositionIndex p, Owner owner){
    this->elephant.a_pos = p;
    this->elephantA_owner = owner;
}
void Position::set_elephantB_pos (PositionIndex p, Owner owner){
    this->elephant.b_pos = p;
    this->elephantB_owner = owner;
}
void Position::set_giraffeA_pos (PositionIndex p, Owner owner){
    this->giraffe.a_pos = p;
    this->giraffeA_owner = owner;
}
void Position::set_giraffeB_pos (PositionIndex p, Owner owner){
    this->giraffe.b_pos = p;
    this->giraffeB_owner = owner;
}

void Position::test(){
    
    std::cout << "operator() test" << std::endl;
    {
        Position s = initial_position();
        std::string initial_print=
            "-------------\n" 
            "        \n"
            "-------------\n"
            "-------------\n"
            "| G | L | E |\n"
            "-------------\n"
            "|   | C |   |\n"
            "-------------\n"
            "|   | c |   |\n"
            "-------------\n"
            "| e | l | g |\n"
            "-------------\n" 
            "-------------\n" 
            "        \n"
            "-------------\n"
        ;
        std::string b3b2_print=
            "-------------\n" 
            "        \n"
            "-------------\n"
            "-------------\n"
            "| G | L | E |\n"
            "-------------\n"
            "|   | c |   |\n"
            "-------------\n"
            "|   |   |   |\n"
            "-------------\n"
            "| e | l | g |\n"
            "-------------\n" 
            "-------------\n" 
            " c      \n"
            "-------------\n"
        ;
        Position b3b2 = initial_position();
        b3b2.set_chickinA_pos(B2, BLACK);
        b3b2.set_chickinB_pos(OB_CHICKIN, BLACK);

        TEST_ASSERT(s() == initial_print);
        TEST_ASSERT(b3b2() == b3b2_print);
    }

    // move generate test
    std::cout << "move_gen test" << std::endl;
    {
        Position b3b2 = initial_position();
        Position c4c3 = initial_position();
        Position b4c3 = initial_position();
        Position b4a3 = initial_position();
        b3b2.set_chickinA_pos(B2, BLACK);
        b3b2.set_chickinB_pos(OB_CHICKIN, BLACK);
        c4c3.set_giraffeA_pos(C3, BLACK);
        b4c3.set_lionA_pos(C3, BLACK);
        b4a3.set_lionA_pos(A3, BLACK);
        std::vector<Position> pos_next = initial_position().gen_move(BLACK);
        for(auto && p : pos_next){
            std::cout << __LINE__ << std::endl;
            std::cout << p() << std::endl;
        }
        auto itr_b3b2 = std::find(pos_next.begin(), pos_next.end(), b3b2);
        auto itr_c4c3 = std::find(pos_next.begin(), pos_next.end(), c4c3);
        auto itr_b4c3 = std::find(pos_next.begin(), pos_next.end(), b4c3);
        auto itr_b4a3 = std::find(pos_next.begin(), pos_next.end(), b4a3);

        TEST_ASSERT(itr_b3b2 != pos_next.end());
        TEST_ASSERT(itr_c4c3 != pos_next.end());
        TEST_ASSERT(itr_b4c3 != pos_next.end());
        TEST_ASSERT(itr_b4a3 != pos_next.end());
    }

    // tsumi test
    std::cout << "is_tsumi test" << std::endl;
    {
        Position tsumi = initial_position();
        tsumi.set_lionB_pos(OB_LION, WHITE);  // 黒の負け 
        TEST_ASSERT(tsumi.is_tsumi(BLACK) ==  true);
        TEST_ASSERT(tsumi.is_tsumi(WHITE) == false);
        tsumi.set_lionB_pos(OB_LION, BLACK);  // 白の負け 
        TEST_ASSERT(tsumi.is_tsumi(BLACK) == false);
        TEST_ASSERT(tsumi.is_tsumi(WHITE) ==  true);
        tsumi.set_lionB_pos(B1, WHITE);
        tsumi.set_lionA_pos(OB_LION, WHITE);  // 黒の負け
        TEST_ASSERT(tsumi.is_tsumi(BLACK) ==  true);
        TEST_ASSERT(tsumi.is_tsumi(WHITE) == false);
        tsumi.set_lionA_pos(OB_LION, BLACK);  // 白の負け
        TEST_ASSERT(tsumi.is_tsumi(BLACK) == false);
        TEST_ASSERT(tsumi.is_tsumi(WHITE) ==  true);
    }{
        Position tri = initial_position();
        tri.set_lionA_pos(C2, BLACK); //黒の負け
        tri.set_lionB_pos(B4, WHITE);
        TEST_ASSERT(tri.is_tsumi(BLACK) ==  true);
        TEST_ASSERT(tri.is_tsumi(WHITE) == false);
        tri = initial_position();
        tri.set_lionA_pos(B1, BLACK); // 白の負け
        tri.set_lionB_pos(A3, WHITE);
        TEST_ASSERT(tri.is_tsumi(BLACK) ==  false);
        TEST_ASSERT(tri.is_tsumi(WHITE) ==   true);
        tri.set_lionA_pos(B4, WHITE);
        tri.set_lionB_pos(C2, BLACK); //黒の負け
        TEST_ASSERT(tri.is_tsumi(BLACK) ==  true);
        TEST_ASSERT(tri.is_tsumi(WHITE) == false);
        tri = initial_position();
        tri.set_lionA_pos(A3, WHITE);
        tri.set_lionB_pos(B1, BLACK); // 白の負け
        TEST_ASSERT(tri.is_tsumi(BLACK) ==  false);
        TEST_ASSERT(tri.is_tsumi(WHITE) ==   true);
    }


    
}
Position Position::initial_position(void){
    Position p;
    p.set_chickinA_pos(B3, BLACK, false);
    p.set_chickinB_pos(B2, WHITE, false);
    p.set_lionA_pos(B4, BLACK);
    p.set_lionB_pos(B1, WHITE);
    p.set_elephantA_pos(A4, BLACK);
    p.set_elephantB_pos(C1, WHITE);
    p.set_giraffeA_pos(C4, BLACK);
    p.set_giraffeB_pos(A1, WHITE);
    return p;
} 

} // namespace AnimalEngine


