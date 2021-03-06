#include "main.h"


QStringList TestCore1Main::getOwList() {
	return {"mEvents"};
}

QStringList TestCore1Main::getDpList() {
	return {};
}

void TestCore1Main::setVars(IVars *v) {
	this->vars = v;
	CM_LOG = reinterpret_cast<ILogger*>(v->get("eLogger"));
}

void TestCore1Main::preInit() {

}

void TestCore1Main::init() {

}

void TestCore1Main::postInit() {

}
ILogger* CM_LOG;

CMEvents::CMEvents(IVars *v, IEvents *o) : org(o){
	CM_LOG->log(ILogLevel::INFO, Q_FUNC_INFO, "CMEvents constructed");
}

void CMEvents::triggerEvent(QString name, QJsonObject o) {	org->triggerEvent(name, o);}
void CMEvents::triggerEvent(QString group, QString name, QJsonObject o) {	org->triggerEvent(group, name, o);}
void CMEvents::addNewEventReciever(IEventsReciever *reciever) {
	CM_LOG->log(ILogLevel::INFO, Q_FUNC_INFO, "Registered new Event reciever");
	org->addNewEventReciever(reciever);
}
void CMEvents::triggerItemEvent(QString name, QJsonObject o) {	org->triggerItemEvent(name, o);}
void CMEvents::triggerToolEvent(QString name, QJsonObject o) {	org->triggerToolEvent(name, o);}
void CMEvents::triggerBlockEvent(QString name, QJsonObject o) {	org->triggerBlockEvent(name, o);}

void *TestCore1Main::get(QString name) {
	CM_LOG->log(ILogLevel::INFO, Q_FUNC_INFO, "Get " + name);

	if(name == "mEvents"){
		if(events == nullptr)	events = new CMEvents(
				vars,
				reinterpret_cast<IEvents*>(vars->getLoader()->getO("mEvents"))
			),
				"mEvents";
		return events;
	}else{
		return nullptr;
	}
}

void *TestCore1Main::getO(QString name) {
	return nullptr;
}

QStringList TestCore1Main::getVarsList() {
	return {"mEvents"};
}
