#include "ModLoader/core/level/mchunk.h"
#include <iostream>

MChunk::MChunk(){}
MChunk::MChunk(IChunkPos p): id(p){
	for(int x = 0 ; x < size; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++)
				if(x > 24){
					if(rand() % 2 == 0) {
						chunk[x][y][z] = new MWorldBlock(Imiks(1, 1, 1, 1), IBlockPos(x, y, z));
					}else{
						chunk[x][y][z] = new MWorldBlock(Imiks(1,1,1,1), IBlockPos(x,y,z), "Parameter1;");
						c++;
					}
				}else{
					chunk[x][y][z] = NULL;
				}

}
MChunk::MChunk(IWorldGenerator *gen, IChunkPos p): id(p){ gen->generateChunk(this);}
MChunk::MChunk(QByteArray a, QJsonObject o, IChunkPos pos): id(pos){
	quint32 id;
	int pr, type, count=0, par=0, npar=0;
	QJsonArray arr = o["params"].toArray();
	QDataStream in(a);
	in.setVersion(QDataStream::Qt_5_4);

	in >> type;
	for ( int x = 0; x < size; x++ )		for ( int y = 0; y < size; y++ )			for ( int z = 0; z < size; z++ ){
				in >> id;
				in >> pr;
				if(id == 0 ){count++;
					this->chunk[x][y][z] = NULL;
				}else if(pr == 0){npar++;
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z)
					);
				}else{par++;
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z),
						arr.at(pr).toString()
					);
				}
			}
	std::cout << "id: " << pos.x() << " " << pos.y() << " " << pos.z() << " " << count << " " << npar << " " << par << "\n";
}
IChunkPos MChunk::getId() {	return this->id;}
IWorldBlock *MChunk::getBlock(IBlockPos p) { return chunk[p.x()][p.y()][p.z()];}
void MChunk::setBlock(IWorldBlock* b){ this->chunk[b->getPos().x()][b->getPos().y()][b->getPos().z()] = b;}
void MChunk::setBlock(IBlockPos pos, IWorldBlock *b) {this->chunk[pos.x()][pos.y()][pos.z()] = b;}
int MChunk::getType() {
	int type;

	if(c == 0) type = 1;
	else if(c <= 256) type = 2;
	else type = 3;

	return type;
}
void MChunk::write(QDataStream& out, QJsonObject& o) {
	QJsonArray arr;

	for ( int x = 0; x < size; x++ )
		for ( int y = 0; y < size; y++ )
			for ( int z = 0; z < size; z++ ) {
				if(chunk[x][y][z] == nullptr){
					out << int(0) << int(0);
				}else	if (chunk[x][y][z]->isParams()) {
					arr << chunk[x][y][z]->getParams();
					out << chunk[x][y][z]->getId().c() << arr.size();
				} else {
					out << chunk[x][y][z]->getId().c() << int(0);
				}
			}

	QJsonObject obj;
	obj["params"] = arr;
	o["chunk"
	  +QString::number(this->id.x())
	  +QString::number(this->id.y())
	  +QString::number(this->id.z())
	] = obj;
}

MPChunk::MPChunk(){}
QColor MPChunk::getBlockColor(IBlockPos pos) {	return QColor(Qt::gray);}


