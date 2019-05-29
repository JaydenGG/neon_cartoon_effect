#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "utils/Utils.h"

using namespace arm_compute;
using namespace utils;

int main(int argc, const char **argv)
{
    Image src_img;
    Image dst_img;
    Image gaus5x5_img;
    Image canny_edge_img;

    if(argc < 2)
    {
        // Print help
        std::cerr << "Usage: ./build/neon_cartoon_effect [input_image.ppm]\n\n";
        std::cerr << "No input_image provided\n";
        return -1;
    }

    // Open PPM file
    PPMLoader ppm;
    ppm.open(argv[1]);

    // Initialize just the dimensions and format of your buffers:
    ppm.init_image(src_img, Format::U8);

    // Initialize just the dimensions and format of the images:
    gaus5x5_img.allocator()->init(*src_img.info());
    canny_edge_img.allocator()->init(*src_img.info());
    dst_img.allocator()->init(*src_img.info());

    NEGaussian5x5             gaus5x5;
    NECannyEdge               canny_edge;
    NEArithmeticSubtraction   sub;

    // Configure the functions to call
    gaus5x5.configure(&src_img, &gaus5x5_img, BorderMode::REPLICATE);
    canny_edge.configure(&src_img, &canny_edge_img, 100, 80, 3, 1, BorderMode::REPLICATE);
    sub.configure(&gaus5x5_img, &canny_edge_img, &dst_img, ConvertPolicy::SATURATE);

    // Now that the padding requirements are known we can allocate the images:
    src_img.allocator()->allocate();
    dst_img.allocator()->allocate();
    gaus5x5_img.allocator()->allocate();
    canny_edge_img.allocator()->allocate();

    // Fill the input image with the content of the PPM image
    ppm.fill_image(src_img);

    // Execute the functions:
    gaus5x5.run();
    canny_edge.run();
    sub.run();

    // Save the result to file:
    save_to_ppm(dst_img, "cartoon_effect.ppm");
}
