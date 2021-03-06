#include "mgenerator.h"
#include <mblock.h>

MWorldGenerator::MWorldGenerator() {}
void MWorldGenerator::generateChunk(IChunk *ch) {
 IAChunkPos pos = ch->getId();int i;
	if(pos.x() % 2 == 0)
	 i = pos.z() % 2 == 0 ? 4 : 6 ;
	else
		i = pos.z() % 2 != 0 ? 4 : 6 ;

	Imiks block(1,i,i,1);

	for ( int x = 0; x < IChunk::size; x++ )
		for ( int y = 0; y < IChunk::size; y++ )
			for ( int z = 0; z < IChunk::size; z++ )
				if((pos.y() == 0) && (y >= 0) && (y < 4)){
					ch->setBlock(IBlockPos(x, y, z), new MWorldBlock(block, IBlockPos(x, y, z)));
				}else{
					ch->setBlock(IBlockPos(x, y, z), nullptr);
				}
}


