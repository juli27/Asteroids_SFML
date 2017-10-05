#pragma once

#include "UIComponent.hpp"

#include <vector>

// a container class containing UIComponents (controls or other containers). it acts as a data
// structure holding components and can also define the layout of it's children within itself
class UIContainer : public UIComponent {
private:
  std::vector<UIComponent&> m_children;

public:

};
