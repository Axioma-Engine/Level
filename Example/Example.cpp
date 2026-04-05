#include <Axiom/Log.h>

int main() {
    AXM::Log logger("Example", AXM::Console::CYAN);

    logger.logInfo("Test");
    logger.logInfo("  Name");
    logger.logInfo("  Age");
    logger.logWarning("uh'oh");
    logger.logError("I warned you");

    return 0;
}
