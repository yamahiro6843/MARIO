#pragma once

#include "UseDxLib.h"
#include "myMath.h"
#include "myMacro.h"
#include "color.h"
#include "Object.h"
#include "Action.h"
#include "BoxBall.h"
#include <memory>

#define SUB_FUNC	private
#define INNER		private
#define MEMBER		public


class myMain : public UseDxLib::MainInterface
{
SUB_FUNC:

	typedef Loki::SingletonHolder<Registry<Mover>> MoverReg;
	typedef Loki::SingletonHolder<Registry<Drawer>> DrawerReg;
	typedef Loki::SingletonHolder<Registry<Autonomy<Action>>> ActionAutonomyReg;
	typedef Loki::SingletonHolder<Deleter<Autonomy<Action>>> ActionDeleter;

private:

	std::vector<std::vector<Box>> _boxes;
	Ball _ball;

MEMBER:
	myMain();

	UseDxLibMessage::MESSAGE init();
	UseDxLibMessage::MESSAGE loop_init();
	UseDxLibMessage::MESSAGE doit();
	UseDxLibMessage::MESSAGE loop_enit();


	UseDxLibMessage::MESSAGE init1();
	UseDxLibMessage::MESSAGE doit1();
};

#undef SUB_FUNC
#undef INNER
#undef MEMBER