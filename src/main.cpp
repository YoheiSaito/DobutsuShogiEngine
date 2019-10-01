#define MAIN_CPP
#include "common.h"

namespace AnimalEngine{
    enum struct EngineMode:int{ Learn = 0, Teach, Play, Test };
}

int main(int argc, char* argv[]) {
    using namespace AnimalEngine;

    boost::property_tree::ptree pt;
    if(argc < 2){
        std::cout << argv[0] << u8" なんとか.ini" << std::endl;
        exit(-1);
    }
    read_ini(argv[1], pt);
    
    std::map<std::string, EngineMode> mode_map = {
        { "Learn"  , EngineMode::Learn }, { "learn"  , EngineMode::Learn }, 
        { "LEARN"  , EngineMode::Learn }, { "Train"  , EngineMode::Learn }, 
        { "train"  , EngineMode::Learn }, { "TRAIN"  , EngineMode::Learn },

        { "Teach"  , EngineMode::Teach }, { "Teach"  , EngineMode::Teach },
        { "TEACH"  , EngineMode::Teach }, { "GenPos" , EngineMode::Teach },
        { "GENPOS" , EngineMode::Teach }, { "genpos" , EngineMode::Teach },
    
        { "Play"   , EngineMode::Play  }, { "play"   , EngineMode::Play  },
        { "PLAY"   , EngineMode::Play  }, { "Game"   , EngineMode::Play  },
        { "game"   , EngineMode::Play  }, { "GAME"   , EngineMode::Play  },

        { "Test"   , EngineMode::Test  }, { "test"   , EngineMode::Test  },
        { "TEST"   , EngineMode::Test  },
    };
    std::map<EngineMode, std::string> mode_unmap = {
        { EngineMode::Learn, "Learn"}, { EngineMode::Teach, "Teach"}, 
        { EngineMode::Play , "Play" }, { EngineMode::Test , "Test" },
    };

    auto ini_mode = pt.get_optional<std::string>("Common.mode");
    if( !ini_mode ){
        std::cerr << "[Common] mode={Learn|Teach|Play|Test}" << std::endl;
        exit(-1);        
    }
    std::string mode_str = ini_mode.get();
    EngineMode mode = mode_map[mode_str];
    switch(mode){
        case EngineMode::Learn:
            learn(pt, mode_unmap[EngineMode::Learn]);
            break;
        case EngineMode::Teach:
            teach(pt, mode_unmap[EngineMode::Teach]);
            break;
        case EngineMode::Play:
            play (pt, mode_unmap[EngineMode::Play ]);
            break;
        case EngineMode::Test:
            test (pt, mode_unmap[EngineMode::Test ]);
            break;
    }
}

