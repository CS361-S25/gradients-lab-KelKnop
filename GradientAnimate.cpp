#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class GradientAnimator : public emp::web::Animate {
    emp::web::Canvas canvas{100, 100, "canvas"};
    std::vector<std::vector<float>> cells;
    int frame = 0;

    public:
    GradientAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        cells.resize(20, std::vector<float>(20, 0));
    }

    void DoFrame() override {
        canvas.Clear();
        frame += 1;

        canvas.Text(emp::Point(10, 10), std::to_string(frame));
        canvas.Rect(10, 10, 10, 10, emp::ColorHSV(0, 0, frame / 1000.0), "black");

        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                float value = cells[x][y];
                canvas.Rect(x * 5, y * 5, 5, 5, emp::ColorHSV(200, 1.0, value), "black");

                // Optional: slowly animate values
                cells[x][y] = std::fmod(cells[x][y] + 0.01f, 1.0f); 
            }
        }
    }
};

GradientAnimator animator;

int main() {
    animator.Step();  // Start the animation loop
    animator.DoFrame();
}
