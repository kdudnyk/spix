/***
 * Copyright (C) Falko Axmann. All rights reserved.
 * Licensed under the MIT license.
 * See LICENSE.txt file in the project root for full license information.
 ****/

#include "GetGlobalPosition.h"

#include <Scene/Scene.h>
#include <Scene/Qt/QtItem.h>
#include <sstream>

namespace spix {
namespace cmd {

GetGlobalPosition::GetGlobalPosition(ItemPath path, std::promise<std::string> promise)
: m_path(std::move(path))
, m_promise(std::move(promise))
{
}

void GetGlobalPosition::execute(CommandEnvironment& env)
{
    auto item = env.scene().itemAtPath(m_path);

    if (item) {
        auto rectPosition = item->getPosition();
        //auto value = item->stringProperty(m_propertyName);
        std::stringstream str;
        str << "Position " << rectPosition.location.x << ":" << rectPosition.location.y ;
        m_promise.set_value(str.str());
    } else {
        m_promise.set_value("NOITEM at " + m_path.string());
        env.state().reportError("GetProperty: Item not found: " + m_path.string());
    }
}

} // namespace cmd
} // namespace spix
