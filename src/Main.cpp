/**
 * @author Ryan Purse
 * Created On: 17/03/2021
 */

#include "RayTracer.h"

int main(int argc, char *argv[])
{
    RayTracer renderer({ 1920, 1080 });  // 640x480, 800x600
    renderer.run();
    return 0;
}
