#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#define PLAYFIELD_WIDTH 10
#define PLAYFIELD_HEIGHT 20
#define BLOCK_SIZE 5
#define SPACE_BETWEEN_BLOCKS 1

enum Pieces{BOX, LONG, TEE, SAW, ZAW, JAY, ELLE};
enum Angles{ANGLE_0, ANGLE_90, ANGLE_180, ANGLE_270};

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

const byte score[] PROGMEM = {
 0x90,76, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,40, 0,214, 0x93,42,
 0x90,72, 0x91,69, 0x92,52, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x90,76, 0x92,52, 0,13,
 0x83, 0,93, 0x93,42, 0x90,74, 0,13, 0x83, 0,93, 0x90,72, 0x91,69, 0x92,40, 0,214, 0x93,42, 0x90,71, 0x91,68,
 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69,
 0x91,64, 0x92,45, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,57, 0,13, 0x83, 0,200, 0x90,76, 0x91,72, 0x92,45, 0,214,
 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x93,42, 0x90,74, 0x91,71, 0x92,45, 0,13, 0x83, 0,200, 0x93,42, 0x90,72,
 0x91,69, 0x92,57, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,44, 0,214, 0x93,42, 0x91,64, 0x92,56, 0,13, 0x83,
 0,200, 0x91,68, 0x92,44, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,56, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40,
 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x90,76, 0x91,72, 0x92,40, 0,214,
 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200,
 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42,
 0x92,57, 0,13, 0x83, 0,200, 0x93,42, 0x92,47, 0,13, 0x83, 0,200, 0x93,42, 0x92,48, 0,13, 0x83, 0,200, 0x92,50,
 0x80, 0x81, 0,214, 0x93,42, 0x90,74, 0x91,65, 0x92,38, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,38, 0x90,77,
 0x91,69, 0,13, 0x83, 0,200, 0x90,81, 0x91,72, 0x82, 0,214, 0x92,38, 0x93,42, 0x91,72, 0,13, 0x83, 0,93, 0x93,42,
 0x91,72, 0,13, 0x83, 0,93, 0x90,79, 0x91,71, 0x92,45, 0,214, 0x93,42, 0x90,77, 0x91,69, 0x92,41, 0,13, 0x83,
 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214, 0x93,42, 0x92,48, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,48,
 0x90,72, 0x91,64, 0,13, 0x83, 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214, 0x93,42, 0x91,69, 0x92,43, 0,13, 0x83,
 0,93, 0x91,67, 0,107, 0x93,42, 0x92,43, 0x90,74, 0x91,65, 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,64, 0x82,
 0,13, 0x83, 0,200, 0x92,47, 0x90,71, 0x91,68, 0,214, 0x93,42, 0x92,59, 0x91,64, 0,13, 0x83, 0,200, 0x90,71,
 0x91,68, 0x82, 0,214, 0x92,59, 0x93,42, 0x90,72, 0x91,69, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x82, 0,214, 0x92,52,
 0x93,42, 0x91,68, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x90,76, 0x91,72, 0x82, 0,214, 0x92,56, 0x93,42,
 0x91,68, 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42, 0x91,64, 0x92,52, 0,13, 0x83, 0,200,
 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42,
 0,13, 0x83, 0,200, 0x93,42, 0x80, 0x81, 0x82, 0,13, 0x83, 0,200, 0x93,42, 0,13, 0x83, 0,200, 0x90,76, 0x91,71,
 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,40, 0,214, 0x93,42, 0x90,72, 0x91,69,
 0x92,52, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x90,76, 0x92,52, 0,13, 0x83, 0,93,
 0x93,42, 0x90,74, 0,13, 0x83, 0,93, 0x90,72, 0x91,69, 0x92,40, 0,214, 0x93,42, 0x90,71, 0x91,68, 0x92,52, 0,13,
 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45,
 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,57, 0,13, 0x83, 0,200, 0x90,76, 0x91,72, 0x92,45, 0,214, 0x93,42, 0x92,57,
 0,13, 0x83, 0,200, 0x93,42, 0x90,74, 0x91,71, 0x92,45, 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,69, 0x92,57,
 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,44, 0,214, 0x93,42, 0x91,64, 0x92,56, 0,13, 0x83, 0,200, 0x91,68,
 0x92,44, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,56, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42,
 0x92,52, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x90,76, 0x91,72, 0x92,40, 0,214, 0x93,42, 0x92,52,
 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64,
 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13,
 0x83, 0,200, 0x93,42, 0x92,47, 0,13, 0x83, 0,200, 0x93,42, 0x92,48, 0,13, 0x83, 0,200, 0x92,50, 0x80, 0x81, 0,214,
 0x93,42, 0x90,74, 0x91,65, 0x92,38, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,38, 0x90,77, 0x91,69, 0,13,
 0x83, 0,200, 0x90,81, 0x91,72, 0x82, 0,214, 0x92,38, 0x93,42, 0x91,72, 0,13, 0x83, 0,93, 0x93,42, 0x91,72, 0,13,
 0x83, 0,93, 0x90,79, 0x91,71, 0x92,45, 0,214, 0x93,42, 0x90,77, 0x91,69, 0x92,41, 0,13, 0x83, 0,200, 0x90,76,
 0x91,67, 0x92,36, 0,214, 0x93,42, 0x92,48, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,48, 0x90,72, 0x91,64,
 0,13, 0x83, 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214, 0x93,42, 0x91,69, 0x92,43, 0,13, 0x83, 0,93, 0x91,67,
 0,107, 0x93,42, 0x92,43, 0x90,74, 0x91,65, 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,64, 0x82, 0,13, 0x83, 0,200,
 0x92,47, 0x90,71, 0x91,68, 0,214, 0x93,42, 0x92,59, 0x91,64, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x82, 0,214,
 0x92,59, 0x93,42, 0x90,72, 0x91,69, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x82, 0,214, 0x92,52, 0x93,42, 0x91,68,
 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x90,76, 0x91,72, 0x82, 0,214, 0x92,56, 0x93,42, 0x91,68, 0,13,
 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42, 0x91,64, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64,
 0x92,45, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0,13, 0x83,
 0,200, 0x93,42, 0x80, 0x81, 0x82, 0,13, 0x83, 0,200, 0x93,42, 0,13, 0x83, 0,200, 0x90,64, 0x91,60, 0x92,57, 0,214,
 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,60, 0x91,57,
 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x92,57, 0,214, 0x93,42,
 0x92,64, 0,13, 0x83, 0,200, 0x90,62, 0x91,59, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x92,56,
 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,59, 0x91,56, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83,
 0,200, 0x93,42, 0x92,56, 0,13, 0x83, 0,200, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,60, 0x91,57, 0x92,57,
 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,57,
 0x91,52, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x92,57, 0,214,
 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,56, 0x91,52, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200,
 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,59, 0x91,56, 0x82, 0,214, 0x93,42, 0,13, 0x83, 0,200,
 0x93,42, 0x80, 0x81, 0,13, 0x83, 0,200, 0x93,42, 0,13, 0x83, 0,200, 0x90,64, 0x91,60, 0x92,57, 0,214, 0x93,42,
 0x92,64, 0,13, 0x83, 0,200, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,60, 0x91,57, 0x92,57,
 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x92,57, 0,214, 0x93,42, 0x92,64,
 0,13, 0x83, 0,200, 0x90,62, 0x91,59, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x92,56, 0,214,
 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,59, 0x91,56, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200,
 0x93,42, 0x92,56, 0,13, 0x83, 0,200, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,60, 0x91,57, 0x92,57, 0,214,
 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,64, 0x91,60, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200,
 0x90,69, 0x91,64, 0x92,57, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x92,57,
 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x90,68, 0x91,62, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83,
 0,200, 0x92,56, 0,214, 0x93,42, 0x92,64, 0,13, 0x83, 0,200, 0x80, 0x81, 0x82, 0,214, 0x93,42, 0,13, 0x83, 0,200,
 0x93,42, 0,13, 0x83, 0,200, 0x93,42, 0,13, 0x83, 0,200, 0x90,76, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x92,52,
 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,40, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,52, 0,13, 0x83, 0,200,
 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x90,76, 0x92,52, 0,13, 0x83, 0,93, 0x93,42, 0x90,74, 0,13, 0x83,
 0,93, 0x90,72, 0x91,69, 0x92,40, 0,214, 0x93,42, 0x90,71, 0x91,68, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64,
 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x90,72, 0x91,69,
 0x92,57, 0,13, 0x83, 0,200, 0x90,76, 0x91,72, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x93,42,
 0x90,74, 0x91,71, 0x92,45, 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,69, 0x92,57, 0,13, 0x83, 0,200, 0x90,71,
 0x91,68, 0x92,44, 0,214, 0x93,42, 0x91,64, 0x92,56, 0,13, 0x83, 0,200, 0x91,68, 0x92,44, 0,214, 0x93,42, 0x90,72,
 0x91,69, 0x92,56, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,93,
 0x93,42, 0,13, 0x83, 0,93, 0x90,76, 0x91,72, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,72,
 0x91,69, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57,
 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x93,42, 0x92,47,
 0,13, 0x83, 0,200, 0x93,42, 0x92,48, 0,13, 0x83, 0,200, 0x92,50, 0x80, 0x81, 0,214, 0x93,42, 0x90,74, 0x91,65,
 0x92,38, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,38, 0x90,77, 0x91,69, 0,13, 0x83, 0,200, 0x90,81, 0x91,72,
 0x82, 0,214, 0x92,38, 0x93,42, 0x91,72, 0,13, 0x83, 0,93, 0x93,42, 0x91,72, 0,13, 0x83, 0,93, 0x90,79, 0x91,71,
 0x92,45, 0,214, 0x93,42, 0x90,77, 0x91,69, 0x92,41, 0,13, 0x83, 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214, 0x93,42,
 0x92,48, 0,13, 0x83, 0,200, 0x82, 0,214, 0x93,42, 0x92,48, 0x90,72, 0x91,64, 0,13, 0x83, 0,200, 0x90,76, 0x91,67,
 0x92,36, 0,214, 0x93,42, 0x91,69, 0x92,43, 0,13, 0x83, 0,93, 0x91,67, 0,107, 0x93,42, 0x92,43, 0x90,74, 0x91,65,
 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,64, 0x82, 0,13, 0x83, 0,200, 0x92,47, 0x90,71, 0x91,68, 0,214, 0x93,42,
 0x92,59, 0x91,64, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x82, 0,214, 0x92,59, 0x93,42, 0x90,72, 0x91,69, 0,13,
 0x83, 0,200, 0x90,74, 0x91,71, 0x82, 0,214, 0x92,52, 0x93,42, 0x91,68, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83,
 0,93, 0x90,76, 0x91,72, 0x82, 0,214, 0x92,56, 0x93,42, 0x91,68, 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45,
 0,214, 0x93,42, 0x91,64, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,52, 0,13,
 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0,13, 0x83, 0,200, 0x93,42, 0x80, 0x81, 0x82, 0,13, 0x83,
 0,200, 0x93,42, 0,13, 0x83, 0,200, 0x90,76, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200,
 0x90,71, 0x91,68, 0x92,40, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,52, 0,13, 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40,
 0,214, 0x93,42, 0x90,76, 0x92,52, 0,13, 0x83, 0,93, 0x93,42, 0x90,74, 0,13, 0x83, 0,93, 0x90,72, 0x91,69,
 0x92,40, 0,214, 0x93,42, 0x90,71, 0x91,68, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42,
 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,57, 0,13, 0x83,
 0,200, 0x90,76, 0x91,72, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x93,42, 0x90,74, 0x91,71, 0x92,45,
 0,13, 0x83, 0,200, 0x93,42, 0x90,72, 0x91,69, 0x92,57, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x92,44, 0,214,
 0x93,42, 0x91,64, 0x92,56, 0,13, 0x83, 0,200, 0x91,68, 0x92,44, 0,214, 0x93,42, 0x90,72, 0x91,69, 0x92,56, 0,13,
 0x83, 0,200, 0x90,74, 0x91,71, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93,
 0x90,76, 0x91,72, 0x92,40, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42,
 0x92,57, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x90,69,
 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,57, 0,13, 0x83, 0,200, 0x93,42, 0x92,47, 0,13, 0x83, 0,200, 0x93,42,
 0x92,48, 0,13, 0x83, 0,200, 0x92,50, 0x80, 0x81, 0,214, 0x93,42, 0x90,74, 0x91,65, 0x92,38, 0,13, 0x83, 0,200,
 0x82, 0,214, 0x93,42, 0x92,38, 0x90,77, 0x91,69, 0,13, 0x83, 0,200, 0x90,81, 0x91,72, 0x82, 0,214, 0x92,38, 0x93,42,
 0x91,72, 0,13, 0x83, 0,93, 0x93,42, 0x91,72, 0,13, 0x83, 0,93, 0x90,79, 0x91,71, 0x92,45, 0,214, 0x93,42,
 0x90,77, 0x91,69, 0x92,41, 0,13, 0x83, 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214, 0x93,42, 0x92,48, 0,13, 0x83,
 0,200, 0x82, 0,214, 0x93,42, 0x92,48, 0x90,72, 0x91,64, 0,13, 0x83, 0,200, 0x90,76, 0x91,67, 0x92,36, 0,214,
 0x93,42, 0x91,69, 0x92,43, 0,13, 0x83, 0,93, 0x91,67, 0,107, 0x93,42, 0x92,43, 0x90,74, 0x91,65, 0,13, 0x83,
 0,200, 0x93,42, 0x90,72, 0x91,64, 0x82, 0,13, 0x83, 0,200, 0x92,47, 0x90,71, 0x91,68, 0,214, 0x93,42, 0x92,59,
 0x91,64, 0,13, 0x83, 0,200, 0x90,71, 0x91,68, 0x82, 0,214, 0x92,59, 0x93,42, 0x90,72, 0x91,69, 0,13, 0x83, 0,200,
 0x90,74, 0x91,71, 0x82, 0,214, 0x92,52, 0x93,42, 0x91,68, 0,13, 0x83, 0,93, 0x93,42, 0,13, 0x83, 0,93, 0x90,76,
 0x91,72, 0x82, 0,214, 0x92,56, 0x93,42, 0x91,68, 0,13, 0x83, 0,200, 0x90,72, 0x91,69, 0x92,45, 0,214, 0x93,42,
 0x91,64, 0x92,52, 0,13, 0x83, 0,200, 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0x92,52, 0,13, 0x83, 0,200,
 0x90,69, 0x91,64, 0x92,45, 0,214, 0x93,42, 0,13, 0x83, 0,200, 0x93,42, 0x80, 0x81, 0x82, 0,13, 0x83, 0,200, 0x93,42,
 0,13, 0x83,
 0xf0
};

Arduboy2 ab;
ArduboyPlaytune tunes(ab.audio.enabled);

class Coordinate{
  public:
    int x, y;
    Coordinate(){}
    Coordinate(int x, int y): x(x), y(y){}
};

class PlayField{
  public:
    bool blocks[PLAYFIELD_WIDTH][PLAYFIELD_HEIGHT];
    byte offset = 2;

    void draw(){
      drawContainer();
      drawBlocks();
    }
    
    void drawContainer(){    
      int w = offset + (BLOCK_SIZE + SPACE_BETWEEN_BLOCKS) * PLAYFIELD_WIDTH;
      int h = (BLOCK_SIZE + SPACE_BETWEEN_BLOCKS) * PLAYFIELD_HEIGHT;
      ab.drawLine(0,0,h,0); // left wall
      ab.drawLine(0,0,0,w + !SPACE_BETWEEN_BLOCKS); // bottom wall
      ab.drawLine(0,w + !SPACE_BETWEEN_BLOCKS,h,w + !SPACE_BETWEEN_BLOCKS); // right wall
    }

    void drawBlocks(){
      for(int i=0; i<PLAYFIELD_WIDTH; i++){
        for(int j=0; j<PLAYFIELD_HEIGHT; j++){
          if(blocks[i][j] == true){
            ab.fillRect(offset+j*(BLOCK_SIZE + SPACE_BETWEEN_BLOCKS),offset+i*(BLOCK_SIZE + SPACE_BETWEEN_BLOCKS),BLOCK_SIZE,BLOCK_SIZE); // rotated x and y axes for vertical screen
            //ab.drawRect(offset+j*(BLOCK_SIZE + SPACE_BETWEEN_BLOCKS),offset+i*(BLOCK_SIZE + SPACE_BETWEEN_BLOCKS),BLOCK_SIZE,BLOCK_SIZE); // rotated x and y axes for vertical screen
          }
        }
      }        
    }

    void clear(){
      for(int i=0; i<PLAYFIELD_WIDTH; i++){
        for(int j=0; j<PLAYFIELD_HEIGHT; j++){
          blocks[i][j] = false;
        }
      }
    }

    bool findLine(byte y){
      for(int i=0; i < PLAYFIELD_WIDTH; i++){
        if(blocks[i][y] == false){
          return false;
        }
      }
      return true;
    }

    void clearLine(byte y){
      for(int i=0; i < PLAYFIELD_WIDTH; i++){
        for(int j=y; j < PLAYFIELD_HEIGHT-1; j++){
          blocks[i][j] = blocks[i][j+1];
        }
      }
    }

    int findAndClearLines(){
      int linesCleared = 0;
      for(int i=0; i<PLAYFIELD_HEIGHT-1; i++){
        if(findLine(i)){
          clearLine(i--); // lines shift downwards when cleared so index must be decremented to check line that was above
          ++linesCleared;
        }
      }
      return linesCleared;
    }
};

class Tetrimino{
  public:
    Coordinate center; // center of the piece
    Coordinate blocks[4][3];
    Pieces piece;
    Angles angle = ANGLE_0;
    
    Tetrimino(){}
    
    Tetrimino(Pieces piece){
      this->piece = piece;
      switch(piece){
        case BOX: 
          setCenter(4, 18); 
          setBlocks(ANGLE_0,   0, 1, 1, 0, 1, 1);
          setBlocks(ANGLE_90,  0, 1, 1, 0, 1, 1);
          setBlocks(ANGLE_180, 0, 1, 1, 0, 1, 1);
          setBlocks(ANGLE_270, 0, 1, 1, 0, 1, 1);
          break;
        case LONG: 
          setCenter(4, 18);
          setBlocks(ANGLE_0,     0, 1, 0, -1, 0, -2);
          setBlocks(ANGLE_90,    -1, 0, 1, 0, 2, 0);
          setBlocks(ANGLE_180,   0, 1, 0, -1, 0, -2);
          setBlocks(ANGLE_270,    -1, 0, 1, 0, 2, 0);
          break;
        case TEE: 
          setCenter(4, 18);
          setBlocks(ANGLE_0,     -1, 0, 1, 0, 0, -1);
          setBlocks(ANGLE_90,    0, 1, -1, 0, 0, -1); 
          setBlocks(ANGLE_180,   -1, 0, 0, 1, 1, 0);
          setBlocks(ANGLE_270,    0, 1, 0, -1, 1, 0);
          break;          
        case SAW: 
          setCenter(4,18);
          setBlocks(ANGLE_0,     -1, 0, 0, 1, 1, 1);
          setBlocks(ANGLE_90,    0, 1, 1, 0, 1, -1); 
          setBlocks(ANGLE_180,     -1, 0, 0, 1, 1, 1);
          setBlocks(ANGLE_270,    0, 1, 1, 0, 1, -1);
          break;
        case ZAW: 
          setCenter(4,18);
          setBlocks(ANGLE_0,     -1, 1, 0, 1, 1, 0);
          setBlocks(ANGLE_90,    1, 1, 1, 0, 0, -1); 
          setBlocks(ANGLE_180,     -1, 1, 0, 1, 1, 0);
          setBlocks(ANGLE_270,    1, 1, 1, 0, 0, -1); 
          break;          
        case JAY: 
          setCenter(5,18);
          setBlocks(ANGLE_0,     -1, 0, 1, 0, 1, -1);
          setBlocks(ANGLE_90,    -1, -1, 0, -1, 0, 1);
          setBlocks(ANGLE_180,     -1, 1, -1, 0, 1, 0);
          setBlocks(ANGLE_270,    0, 1, 1, 1, 0, -1); 
          break;
        case ELLE: 
          setCenter(5,18);
          setBlocks(ANGLE_0,     -1, 0, 1, 0, -1, -1);
          setBlocks(ANGLE_90,    0, 1, 0, -1, 1, -1);
          setBlocks(ANGLE_180,     -1, 0, 1, 0, 1, 1);
          setBlocks(ANGLE_270,    -1, 1, 0, 1, 0, -1);
          break;
      }
    }

    void setCenter(byte x, byte y){
      center = Coordinate(x, y);
    }

    void setBlocks(Angles angle, int block0x, int block0y, int block1x, int block1y, int block2x, int block2y){
      blocks[angle][0].x = block0x;
      blocks[angle][0].y = block0y;
      blocks[angle][1].x = block1x;
      blocks[angle][1].y = block1y;
      blocks[angle][2].x = block2x;
      blocks[angle][2].y = block2y;
    }
        
    int minX(){
      int minBlock = 0;
      for(int i=0; i<COUNT_OF(blocks[angle]); i++){
        if(blocks[angle][i].x < blocks[angle][minBlock].x){
          minBlock = i;
        }
      }
      if(center.x < blocks[angle][minBlock].x){
        return -1;
      }
      else{
        return minBlock;
      }
    }
    
    int maxX(){
      int maxBlock = 0;
      for(int i=0; i<COUNT_OF(blocks[angle]); i++){
        if(blocks[angle][i].x > blocks[angle][maxBlock].x){
          maxBlock = i;
        }
      }
      if(center.x > center.x + blocks[angle][maxBlock].x){
        return -1;
      }
      else{
        return maxBlock;
      }
    }
    
    int minY(){
      int minBlock = 0;
      for(int i=0; i<COUNT_OF(blocks[angle]); i++){
        if(blocks[angle][i].y < blocks[angle][minBlock].y){
          minBlock = i;
        }
      }
      if(center.y < blocks[angle][minBlock].y){
        return -1;
      }
      else{
        return minBlock;
      }
    }
};

class Game{
  public:
    bool gameStarted;
    bool gameOver;    
    int linesCleared;
    int score;
    long prevMillis;
    PlayField field;
    Tetrimino selected;
    char message[20];
    int dropDelay = 600;
    long lastDroppedMillis;

    int level = 0;
    bool soundEffects = true;
    int musicTrack = 0;
    bool paused;

    void start(){
      field.clear();
      gameStarted = true;
      gameOver = false;
      linesCleared = 0;
      score = 0;
    }

    void menu(){
      gameOver = false;
      gameStarted = false;
      
      while(ab.pressed(A_BUTTON)){
      }
      ab.clear();
      ab.setCursor(0,0);
      ab.println("PRESS ANY BUTTON");
      ab.setCursor(0,10);
      ab.println("TO PLAY");

      ab.setCursor(0,54);
      ab.println("PAUSE = UP Button");
      
      if(anyButtonPressed()){
        start();
      }
    }

    bool anyButtonPressed(){      
      return ab.pressed(A_BUTTON) || ab.pressed(B_BUTTON) || ab.pressed(UP_BUTTON) || ab.pressed(LEFT_BUTTON) || ab.pressed(DOWN_BUTTON) || ab.pressed(RIGHT_BUTTON);
    }

    bool spawnBlocked(){

      if(field.blocks[selected.center.x][selected.center.y] == true){
        return true;
      }

      for(int i=0; i<COUNT_OF(selected.blocks[selected.angle]); i++){
        if(field.blocks[selected.center.x + selected.blocks[selected.angle][i].x][selected.center.y + selected.blocks[ANGLE_0][i].y] == true){
          return true;
        }
      }
      
      return false;
    }
    
    void spawnPiece(){
      selected = randomPiece();

      if(spawnBlocked()){
        gameOver = true;
        return;
      }

      field.blocks[selected.center.x][selected.center.y] = true;

      for(int i=0; i<COUNT_OF(selected.blocks[selected.angle]); i++){
        field.blocks[selected.center.x + selected.blocks[ANGLE_0][i].x][selected.center.y + selected.blocks[ANGLE_0][i].y] = true;
      }
    }

    bool hitBottom(){
      int i = selected.minY();
      
      // center block check      
      if(i == -1 && selected.center.y == 0){
        return true;
      }
      // lowest block check
      if (selected.center.y + selected.blocks[selected.angle][i].y == 0){
        return true;
      }
      return false;
    }

     bool hitAnotherBlock(int offsetX, int offsetY){
      if(field.blocks[selected.center.x+offsetX][selected.center.y+offsetY] == true && isSelectedPiece(selected.center.x+offsetX, selected.center.y+offsetY) == false){
        return true;
      }

      for(int i=0; i<COUNT_OF(selected.blocks[selected.angle]); i++){
        int x = selected.center.x + selected.blocks[selected.angle][i].x + offsetX;
        int y = selected.center.y + selected.blocks[selected.angle][i].y + offsetY;
        if(isSelectedPiece(x,y) == false && field.blocks[x][y] == true){
          return true;
        }
      }
      return false;
     }

    bool canDropPiece(){
      if(hitBottom()){
        return false;
      }
      if(hitAnotherBlock(0,-1)){
        return false;
      }
      return true;
    }

    void dropPiece(){
      if(canDropPiece() == false){
        return;
      }
      
      drawPiece(false);   
      --selected.center.y;
      drawPiece(true);
    }

    void drawPiece(bool state){
      field.blocks[selected.center.x][selected.center.y] = state;
      for(int i=0; i<COUNT_OF(selected.blocks[selected.angle]); i++){
        field.blocks[selected.center.x+selected.blocks[selected.angle][i].x][selected.center.y+selected.blocks[selected.angle][i].y] = state;
      }
    }

    bool isSelectedPiece(byte x, byte y){
      for(int i=0; i<COUNT_OF(selected.blocks[selected.angle]); i++){
        if(x == selected.center.x + selected.blocks[selected.angle][i].x && y == selected.center.y + selected.blocks[selected.angle][i].y){
          return true;
        }
      }
      if(selected.center.x == x && selected.center.y == y){
        return true;
      }
      return false;
    }

    void rotatePiece(bool dir){
      int newAngle = selected.angle;
      if(dir == true){
        if(newAngle == ANGLE_270){
          newAngle = ANGLE_0;  
        }
        else{
          newAngle = newAngle + 1;
        }              
      }
      else if (dir == false){
        if(newAngle == ANGLE_0){
          newAngle = ANGLE_270;
        }
        else{
          newAngle = newAngle - 1;
        }
      }

      for(int i=0; i<COUNT_OF(selected.blocks[newAngle]); i++){
        int newX = selected.center.x + selected.blocks[newAngle][i].x;
        int newY = selected.center.y + selected.blocks[newAngle][i].y;

        if(newX < 0 || newX > PLAYFIELD_WIDTH-1){
          return;
        }
        if(newY < 0 || newY > PLAYFIELD_HEIGHT-1){
          return;  
        }
        if(field.blocks[newX][newY] == true){
          return;
        }
        
      }

      selected.angle = newAngle;
    }

    bool hitLeftWall(){
      int i = selected.minX();
      
      // center block check      
      if(i == -1 && selected.center.x == 0){
        return true;
      }
      // lowest block check
      if (selected.center.x + selected.blocks[selected.angle][i].x == 0){
        return true;
      }
      return false;
    }

    void movePieceLeft(){
      if(hitLeftWall() || hitAnotherBlock(-1,0)){
        return;
      }            
      drawPiece(false);
      selected.center.x--; 
      drawPiece(true);      
    }

    bool hitRightWall(){
      int i = selected.maxX();
    
      // center block check
      if(i == -1 && selected.center.x == PLAYFIELD_WIDTH-1){
        return true;
      }
      // highest block check
      if (selected.center.x + selected.blocks[selected.angle][i].x == PLAYFIELD_WIDTH-1){
        return true;
      }
      return false;
    }

    void movePieceRight(){
      if(hitRightWall() || hitAnotherBlock(1,0)){
        return;
      }
      drawPiece(false);
      selected.center.x++; 
      drawPiece(true);
    }

    Tetrimino randomPiece(){      
      return Tetrimino(random(7));
    }

};

Game game;

void setup() {
  ab.boot();
  ab.setFrameRate(60);
  ab.initRandomSeed();
    
  tunes.initChannel(PIN_SPEAKER_1);
  tunes.toneMutesScore(true);
  ab.audio.on();

  Serial.begin(9600);
  
  game = Game(); 
  game.message[19] = '\0';
}

void loop() {
  if (!(ab.nextFrame()))
    return;

  if(game.gameStarted == false){
    game.menu();
  }
  else if(game.gameOver == false){
    ab.clear();
    ab.println(game.message);
    
    if (!tunes.playing() && game.soundEffects)
      tunes.playScore(score);

    if(millis() > game.lastDroppedMillis + game.dropDelay){
      if(game.canDropPiece() == false){
          game.linesCleared += game.field.findAndClearLines();
          game.level = game.linesCleared / 10;          
          game.dropDelay = 200 + 400/(game.level+1);
          game.spawnPiece();
      }
      else{
        game.dropPiece();
      }
      game.lastDroppedMillis = millis();
    }
    
    if(millis() > game.prevMillis + 70){
      if(ab.pressed(A_BUTTON)){
        game.drawPiece(false);
        game.rotatePiece(true);
        game.drawPiece(true);
        while(ab.pressed(A_BUTTON));
      }
      else if (ab.pressed(B_BUTTON)){
        game.drawPiece(false);
        game.rotatePiece(false);
        game.drawPiece(true);
        while(ab.pressed(B_BUTTON));
      }
      if(ab.pressed(DOWN_BUTTON)){
        game.dropPiece();
      }
      else if(ab.pressed(UP_BUTTON)){
        while(ab.pressed(UP_BUTTON));
        game.paused = true;
        ab.invert(true);
        ab.audio.off();
        while(game.paused == true){
          if(ab.pressed(UP_BUTTON)){
            game.paused = false;
            ab.invert(false);
            ab.audio.on();
          }
          delay(50);
        }
      }
      if(ab.pressed(LEFT_BUTTON)){
        game.movePieceLeft();
      }
      else if(ab.pressed(RIGHT_BUTTON)){
        game.movePieceRight();
      }
      game.prevMillis = millis();
    }
    game.field.draw();
  }
  else if(game.gameOver == true){
    ab.clear();
    ab.setCursor(0,0);
    ab.print("Lines: ");
    ab.println(game.linesCleared);
    ab.print("Level: ");
    ab.println(game.level);    
    tunes.stopScore();
    delay(1000);
    if(game.anyButtonPressed()){
      game.menu();
    }
  }

  Serial.write(ab.getBuffer(), 128 * 64 / 8);
  ab.display();
}
