#pragma once
//#include <utility>
//#include <vector>
//#include "Framework.h"

#include "Upgrade.h"

class Shield : public Upgrade
{
public:
	Shield(std::pair<float, float> pos);
	void activate(std::pair<float, float> pos) override;
	~Shield();
};

