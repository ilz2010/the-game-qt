#include <mchunk.h>

// MChunk
MChunk::MChunk(){}

MChunk::MChunk(IWorldGenerator *gen, IAChunkPos p) : id(p){ gen->generateChunk(this);}

MChunk::MChunk(QByteArray a, QJsonObject o, IAChunkPos pos): id(pos){
	quint32 id;
	int pr, type;
	QJsonArray arr = o["params"].toArray();
	QDataStream in(a);
	in.setVersion(QDataStream::Qt_5_4);

	in >> type;
	for ( int x = 0; x < size; x++ )		for ( int y = 0; y < size; y++ )			for ( int z = 0; z < size; z++ ){
				in >> id;
				in >> pr;
				if(id == 0 ){
					this->chunk[x][y][z] = NULL;
				}else if(pr == 0){
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z)
					);
				}else{
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z),
						arr.at(pr).toString()
					);
				}
			}
}


IWorldBlock *MChunk::getBlock(IBlockPos p) { return chunk[p.x()][p.y()][p.z()];}

void MChunk::setBlock(IWorldBlock* b){ this->chunk[b->getPos().x()][b->getPos().y()][b->getPos().z()] = b;}

void MChunk::setBlock(IBlockPos pos, IWorldBlock *b) {this->chunk[pos.x()][pos.y()][pos.z()] = b;}

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


void MChunk::reParseSides(){
	for(int x = 0 ; x < size ; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++){
				if(chunk[x][y][z] != nullptr) {
					if((x > 0)  && (chunk[x - 1][y][z] == nullptr)){ rSides[x][y][z] |= IBSides::Left;		}
					if((x < 31) && (chunk[x + 1][y][z] == nullptr)){ rSides[x][y][z] |= IBSides::Right;		}
					if((y > 0)  && (chunk[x][y - 1][z] == nullptr)){ rSides[x][y][z] |= IBSides::Bottom;		}
					if((y < 31) && (chunk[x][y + 1][z] == nullptr)){ rSides[x][y][z] |= IBSides::Top;		}
					if((z > 0)  && (chunk[x][y][z - 1] == nullptr)){ rSides[x][y][z] |= IBSides::Back;		}
					if((z < 31) && (chunk[x][y][z + 1] == nullptr)){ rSides[x][y][z] |= IBSides::Front;		}
				}else{
					rSides[x][y][z] = 0;
				}
			}
}

void MChunk::onReAlloc() {
	if(!textures) textures = varG(ITextureManager*, "mBTex");

	reParseSides();
 bool f = true;
 glNewList(rList, GL_COMPILE);
 glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for(int x = 0 ; x < size ; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++)
			if(rSides[x][y][z] != 0){ // TODO Rewrite render on MChunk
				if(f) textures->bindTexture(chunk[x][y][z]->getId()), f = false;
				drawCube(x, y, z);
			}
 glBindTexture(0,0);
	glEndList();
}

void MChunk::drawCube(int x, int y, int z) {
	MRHelper::drawTCubeS(getBlockPos(x, y, z), rSides[x][y][z]);
}
// MChunk


// MPChunk
MPChunk::MPChunk(){}

QColor MPChunk::getBlockColor(IBlockPos pos) {	return QColor(Qt::gray);}

void MPChunk::onReAlloc() {
	// TODO: Render
}
// MPChunk

