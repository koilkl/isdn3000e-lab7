#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

void task1() {

    rs2::pipeline pipe;
    rs2::config cfg;

    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    pipe.start(cfg);

    while (true) {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::video_frame color_frame = frames.get_color_frame();

        if (!color_frame) continue;

        cv::Mat img(
            cv::Size(color_frame.get_width(), color_frame.get_height()),
            CV_8UC3,
            (void*)color_frame.get_data(),
            cv::Mat::AUTO_STEP
        );

        cv::Mat frame = img.clone();


        // =========================
        // TODO 1: Crop
        // =========================


        // =========================
        // TODO 2: Grayscale
        // =========================


        // =========================
        // TODO 3: Blur
        // =========================
        cv::Mat blur_avg, blur_gauss;
        // Average Blur (linear)
        // Example kernel (3x3) you can extend it to 4x4, 5x5, etc.:
        // [1/9 1/9 1/9
        //  1/9 1/9 1/9
        //  1/9 1/9 1/9]


        // Gaussian Blur
        // Example kernel (3x3) you can extend it to 4x4, 5x5, etc.:
        // [1 2 1
        //  2 4 2
        //  1 2 1] / 16


        // =========================
        // TODO 4: Sharpen
        // =========================
        // Sharpen using Laplacian + Identity
        // Example kernel (3x3):
        // [  0 -1  0
        //   -1  5 -1
        //    0 -1  0 ]


        // =========================
        // TODO 5: Edge Detection
        // =========================
        cv::Mat edge_lap, edge_canny;
        // Edge detection using Laplacian
        // Example kernel (3x3):
        // [  0 -1  0
        //   -1  4 -1
        //    0 -1  0 ]


        // Canny edge detection


        // =========================
        // TODO 6: Custom Kernel
        // =========================
        // cv::Mat custom;
        // cv::Mat kernel = (cv::Mat_<float>(3,3) <<
        //     -1, -1, -1,
        //     -1,  8, -1,
        //     -1, -1, -1
        // );
        // cv::filter2D(gray, custom, -1, kernel);

        // =========================
        // Display
        // =========================
        // cv::imshow("Crop", crop);
        // cv::imshow("Gray", gray);
        // cv::imshow("Blur (Average)", blur_avg);
        // cv::imshow("Blur (Gaussian)", blur_gauss);
        // cv::imshow("Sharpen (Laplacian+Identity)", sharp);
        // cv::imshow("Edge (Laplacian)", edge_lap);
        // cv::imshow("Edge (Canny)", edge_canny);
        // cv::imshow("Custom Kernel", custom);


        int key = cv::waitKey(1);
        if (key == 27) break;
    }

    cv::destroyAllWindows();
}