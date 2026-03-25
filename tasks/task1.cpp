#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>

void task1() {

    rs2::pipeline pipe;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_YUYV, 15);
    // 2. 如果你不需要深度图，直接注释掉深度流的配置！
    // cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 15);

    pipe.start(cfg);

    while (true) {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::video_frame color_frame = frames.get_color_frame();

        if (!color_frame) continue;

        // =========================
        // 【关键修改】因为是 YUYV 格式，OpenCV 要转一下 BGR
        // =========================
        cv::Mat img_yuyv(
            cv::Size(color_frame.get_width(), color_frame.get_height()),
            CV_8UC2, // YUYV 是 2 通道格式
            (void*)color_frame.get_data(),
            cv::Mat::AUTO_STEP
        );
        cv::Mat frame;
        cv::cvtColor(img_yuyv, frame, cv::COLOR_YUV2BGR_YUYV); // YUYV 转 BGR

        // =========================
        // TODO 1-6：你的图像处理代码完全不变！
        // =========================
        cv::Rect box(180,100,200,200);
        cv::Mat crop = frame(box).clone();

        cv::Mat gray;
        cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);

        cv::Mat blur_avg, blur_gauss;
        cv::blur(gray,blur_avg,cv::Size(3,3));
        cv::GaussianBlur(gray,blur_gauss,cv::Size(3,3),0);

        cv::Mat gray_f, lap, sharp;
        gray.convertTo(gray_f, CV_32F);
        cv::Laplacian(gray_f, lap, CV_32F);
        sharp = gray_f + lap;
        sharp.convertTo(sharp, CV_8U);

        cv::Mat edge_lap, edge_canny;
        cv::Laplacian(gray, edge_lap, CV_16S, 3);
        cv::convertScaleAbs(edge_lap, edge_lap);
        cv::Canny(gray, edge_canny, 80, 150);

        cv::Mat custom;
        cv::Mat kernel = (cv::Mat_<float>(3,3) <<
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
        );
        cv::filter2D(gray, custom, -1, kernel);

        // =========================
        // Display
        // =========================
        cv::imshow("Crop", crop);
        cv::imshow("Gray", gray);
        cv::imshow("Blur (Average)", blur_avg);
        cv::imshow("Blur (Gaussian)", blur_gauss);
        cv::imshow("Sharpen (Laplacian+Identity)", sharp);
        cv::imshow("Edge (Laplacian)", edge_lap);
        cv::imshow("Edge (Canny)", edge_canny);
        cv::imshow("Custom Kernel", custom);

        int key = cv::waitKey(1);
        if (key == 27) break;
    }

    cv::destroyAllWindows();
}