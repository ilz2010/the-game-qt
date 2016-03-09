#ifndef GLOBALQT_MPLUGIN_H
#define GLOBALQT_MPLUGIN_H
#include <idefines.h>

class MPluginsContainer {
 QList<IMod*>* plugins;

public:
	MPluginsContainer();

	void preInit();
	void init();
	void postInit();
};


#endif //GLOBALQT_MPLUGIN_H
