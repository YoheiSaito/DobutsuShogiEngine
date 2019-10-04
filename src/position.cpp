#include "position.hpp"


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
    std::unordered_map<char, bool> emage_flags = {
        {'c', false}, {'l', false}, {'e', false}, {'g', false}, 
    };
    std::unordered_map<char,PositionSeperator> mp_rf= {
        {'e', elephant}, {'g', giraffe}, {'l', lion},
        {'E', elephant}, {'G', giraffe}, {'L', lion},
        {'C',  chickin}, {'h', chickin},
        {'c',  chickin}, {'H', chickin}, 
    };
    bool ela = elephantA_owner;
    bool gra = giraffeA_owner;
    bool lra = lionA_owner;
    bool cra = chickinA_owner;
    std::unordered_map<char,uint8_t> owner_a = {
        {'e', ela}, {'g', gra}, {'l', lra}, {'C', cra}, {'h', cra},
        {'E', ela}, {'G', gra}, {'L', lra}, {'c', cra}, {'H', cra},
    };
    bool elb = elephantA_owner;
    bool grb = giraffeA_owner;
    bool lrb = lionA_owner;
    bool crb = chickinA_owner;
    std::unordered_map<char,uint8_t> owner_b = {
        {'e', elb}, {'g', grb}, {'l', lrb}, {'C', crb}, {'h', crb},
        {'E', elb}, {'G', grb}, {'L', lrb}, {'c', crb}, {'H', crb},
    };

    auto putted = std::get<0>(board);
    auto having = turn ? std::get<1>(board): std::get<2>(board);
    // put
    for(auto&& p : having){ // todo 順序を利用したcontinue <-> unordered_map
        if(!emage_flags[p] ){
            emage_flags[p] = true;
            for(int i = 0; i < OB; i++){
                if(putted[i] ==' '){
                    if       (owner_a[p] == turn && mp_rf[p].a_pos >= OB){
                        auto tmp = mp_rf[p].a_pos;
                        mp_rf[p].a_pos = i;
                        poses.push_back(*this);
                        mp_rf[p].a_pos =tmp;
                    } else if(owner_b[p] == turn && mp_rf[p].b_pos >= OB){
                        auto tmp = mp_rf[p].b_pos;
                        mp_rf[p].b_pos = i;
                        poses.push_back(*this);
                        mp_rf[p].b_pos = tmp;
                    }
                }
            }
        }
    }
    // move
    /* pos.push_back(*this); */
    return poses;
}
/* Position Position::move(Move mv, Turn turn, boost::optional<BoardMap> mp){ */
/*     BoardMap bm = mp ? mp.get():  make_map(); */
/*     Position p = *this; */
/*     auto koma = std::get<0>(bm)[mv.dst]; */
/*     if(std::get<0>(bm)[mv.src]){ */
/*     } */

/*     return p; */
/* } */

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
    int b = 0, w = 0;
    for(auto&& c : board) c = ' ';
    for(auto&& c : black) c = ' ';
    for(auto&& c : white) c = ' ';

    char cb = chickinA_promote ? 'h':'c';
    char cw = chickinA_promote ? 'H':'C';
    char cc = elephantA_owner == Turn::BLACK? cb:cw;
    if(chickin.a_pos < 12)
        board[chickin.a_pos] = cc;
    else 
        (chickinA_owner == BLACK?black[0]:white[0]) = cc;
    cb = chickinB_promote ? 'h':'c';
    cw = chickinB_promote ? 'H':'C';
    cc = elephantA_owner == Turn::BLACK? cb:cw;
    if(chickin.b_pos < 12)
        board[chickin.b_pos] = cc;
    else
        (chickinB_owner == BLACK?black[1]:white[1]) = cc;

    char ce = elephantA_owner == Turn::BLACK?'e':'E';
    if(elephant.a_pos < 12)
        board[elephant.a_pos] = ce;
    else 
        (elephantA_owner == BLACK?black[2]:white[2]) = ce;
    if(elephant.b_pos < 12)
        board[elephant.b_pos] = ce;
    else
        (elephantB_owner == BLACK?black[3]:white[3]) = ce;

    char cg = giraffeA_owner == Turn::BLACK?'g':'G';
    if(giraffe.a_pos < 12)
        board[giraffe.a_pos] = cg;
    else 
        (giraffeA_owner == BLACK?black[4]:white[4]) = cg;
    if(giraffe.b_pos < 12)
        board[giraffe.b_pos] = cg;
    else
        (giraffeB_owner == BLACK?black[5]:white[5]) = cg;

    char cl = giraffeA_owner == Turn::BLACK?'l':'L';
    if(lion.a_pos < 12)
        board[lion.a_pos] =  cl;
    else 
        (lionA_owner == BLACK?black[6]:white[6]) = cl;
    if(lion.b_pos < 12)
        board[lion.b_pos] =  cl;
    else 
        (lionB_owner == BLACK?black[7]:white[7]) = cl;

    return std::make_tuple(board, black, white);
}


void Position::set_chickinA_pos (PositionIndex p, Owner owner, bool promote){
    this->chickin.a_pos = p;
    this->chickinA_owner = owner;
    chickinA_promote = promote;
}
void Position::set_chickinB_pos (PositionIndex p, Owner owner, bool promote){
    this->chickin.b_pos = p;
    this->chickinB_owner = owner;
    chickinB_promote = promote;
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
    
    // print
    std::cout << "operator() test" << std::endl;
    {
        Position s = initial_position();
        std::string initial_print=
            "-------------\n" 
            "      \n"
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
            "      \n"
            "-------------\n"
        ;
        std::string b3b2_print=
            "-------------\n" 
            "      \n"
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
            "c     \n"
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

}


