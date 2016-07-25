#include <jni.h>
#include <android/log.h>
#include <Substrate.h>

#define LOG_TAG "CustomBlock"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

#include "minecraftpe/client/renderer/block/BlockGraphics.h"
#include "minecraftpe/world/item/BlockItem.h"
#include "minecraftpe/world/material/Material.h"

Block* Block::mCustomBlock;

static void (*_Block$initBlocks)();
static void Block$initBlocks() {
	_Block$initBlocks();
	
	Block::mBlocks[252] = Block::mCustomBlock = (new Block("customBlock", 252, Material::getMaterial(MaterialType::STONE)))->setCategory(CreativeItemCategory::BLOCKS)->init();
}

static void (*_Item$initItems)();
static void Item$initItems(){
	Item::mItems[Block::mCustomBlock->blockId] = new BlockItem(Block::mCustomBlock->getDescriptionId(), Block::mCustomBlock->blockId - 256);
	
	_Item$initItems();
}

static void (*_Item$initCreativeItems)();
static void Item$initCreativeItems() {
	_Item$initCreativeItems();
	
	Item::addCreativeItem(Block::mCustomBlock, 0);
}

static void (*_BlockGraphics$initBlocks)();
static void BlockGraphics$initBlocks() {
	_BlockGraphics$initBlocks();
	
	BlockGraphics::mBlocks[Block::mCustomBlock->blockId] = new BlockGraphics("dirt");
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

	MSHookFunction((void*) &Block::initBlocks, (void*) &Block$initBlocks, (void**) &_Block$initBlocks);
	MSHookFunction((void*) &Item::initItems, (void*) &Item$initItems, (void**) &_Item$initItems);
	MSHookFunction((void*) &Item::initCreativeItems, (void*) &Item$initCreativeItems, (void**) &_Item$initCreativeItems);
	MSHookFunction((void*) &BlockGraphics::initBlocks, (void*) &BlockGraphics$initBlocks, (void**) &_BlockGraphics$initBlocks);
	
	return JNI_VERSION_1_2;
}
