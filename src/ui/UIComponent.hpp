#pragma once

// base class for all things UI

class UIComponent {
private:

protected:
  // flag whether it is required to update the component or not
  // used within the components update function after input checking?
  bool m_dirty;

public:
};
