//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef CONTEXT_H
#define CONTEXT_H
#include "GameContext.h"

namespace Context {
    inline std::unique_ptr<GameContext> *GlobalContext = nullptr;
}
#endif //CONTEXT_H
