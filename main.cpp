#include "logarsh.h"
#include <iostream>
#include <fstream>

int main()
{
	logger.info("test","ceci est une info");
	logger.error("test","ceci est une erreur");
	logger.startInit("Game");
	logger.initLog("Loading windows");
	logger.initLog("Loading texture");
	logger.endInit();
	logger.info("test", "ceci est une info");
	logger.error("test", "ceci est une erreur");
	logger.startInit("Game");
	logger.initLog("Loading windows");
	logger.initLog("Loading texture");
	logger.endInit();
	logger.info("test", "ceci est une info");
	logger.error("test", "ceci est une erreur");
	logger.startInit("Game");
	logger.initLog("Loading windows");
	logger.initLog("Loading texture");
	logger.endInit();
	logger.info("test", "ceci est une info");
	logger.error("test", "ceci est une erreur");
	logger.startInit("Game");
	logger.initLog("Loading windows");
	logger.initLog("Loading texture");
	logger.endInit();
	logger.info("test", "ceci est une info");
	logger.error("test", "ceci est une erreur");
	logger.startInit("Game");
	logger.initLog("Loading windows");
	logger.initLog("Loading texture");
	logger.endInit();

	return EXIT_SUCCESS;
}