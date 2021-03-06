#include <mods/mtext.h>
#include <mutils.h>

MTextContainer::MTextContainer(){}

void MTextContainer::preInit() {
	QList<QJsonObject> lst;
		for(QFileInfo i : QDir("mods/mods").entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			QDir d("mods/mods/"+i.fileName());
			QJsonObject o = loadJson(d.filePath("text.dat"));
			o.insert("path", d.absolutePath()+"/");
			lst << o;
		}

	//MItemsContainer
	{
		QMap<QString, Imiks> *iidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, IItem *> *itemsMap = new QMap<Imiks, IItem *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			for(QJsonObject o : lst) {
				m = o["name"].toString();
					for(QJsonValue v : o["items"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) { cm++;lm = m; }
						if (i != li) { ci++;li = i; }
						if (k != lk) { ck++;lk = k; }
						if (s != ls) { cs++;ls = s; }

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = Imiks(cm, ci, ck, cs);

						iidsMap->insert(n, e);
						itemsMap->insert(e, new MItem(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mIids = new MIIds(iidsMap);
		mIic = new MItemsContainer(itemsMap);
  mItex = varN(ITextureManager*, "nTextureManager");
		mItex->loadTextures(texMap);

		varS(mIids, "mIIds");
		varS(mIic, "mItems");
		varS(mItex, "mITex");
		logD("Items count: "+QString::number(itemsMap->size()));
	}
	//!MItemsContainer
	//MBlocksContainer
	{
		QMap<QString, Imiks> *bidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, IBlock *> *blocksMap = new QMap<Imiks, IBlock *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			for(QJsonObject o : lst) {
				m = o["name"].toString();
					for(QJsonValue v : o["blocks"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) { cm++;lm = m; }
						if (i != li) { ci++;li = i; }
						if (k != lk) { ck++;lk = k; }
						if (s != ls) { cs++;ls = s; }

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = Imiks(cm, ci, ck, cs);

						bidsMap->insert(n, e);
						blocksMap->insert(e, new MBlock(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mBids = new MBIds(bidsMap);
		mBic = new MBlocksContainer(blocksMap);
		mBtex = varN(ITextureManager*, "nTextureManager");
		mBtex->loadTextures(texMap);

		varS(mBids, "mBIds");
		varS(mBic, "mBlocks");
		varS(mBtex, "mBTex");
		logD("Blocks count: "+QString::number(blocksMap->size()));
	}
	//!MBlocksContainer
 //MToolsContainer
	{
		QMap<QString, Imiks> *tidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, ITool *> *toolsMap = new QMap<Imiks, ITool *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			for(QJsonObject o : lst) {
				m = o["name"].toString();
					for(QJsonValue v : o["tools"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) {cm++;	lm = m;	}
						if (i != li) {ci++;	li = i;	}
						if (k != lk) {ck++;	lk = k;	}
						if (s != ls) {cs++;	ls = s;	}

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = Imiks(cm, ci, ck, cs);

						tidsMap->insert(n, e);
						toolsMap->insert(e, new MTool(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mTids = new MTIds(tidsMap);
		mTic = new MToolsContainer(toolsMap);
		mTtex = varN(ITextureManager*, "nTextureManager");
		mTtex->loadTextures(texMap);

		varS(mTids, "mTIds");
		varS(mTic, "mTools");
		varS(mTtex, "mTTex");
		logD("Tools count: "+QString::number(toolsMap->size()));
	}
	//!MToolsContainer
}

void MTextContainer::init() {

}

void MTextContainer::postInit() {

}
