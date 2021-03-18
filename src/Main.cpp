/**
 * @author Ryan Purse
 * Created On: 17/03/2021
 */

#include "RayTracer.h"

int main(int argc, char *argv[])
{
    RayTracer renderer({ 400, 400 });
    renderer.updateAndHold();
    return 0;
}
