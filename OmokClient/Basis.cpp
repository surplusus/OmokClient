#include "stdafx.h"
#include "Basis.h"
#include "GameBoard.h"
#include "Client.h"
void Subject::Notify(TYPE_EVENT event)
{
	observer_->onNotify(this, event);
}

void Subject::Register(Observer * ob)
{
	observer_ = ob;
}

Basis::Basis()
{
}
