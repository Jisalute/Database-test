#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

int largestRectangleArea(std::vector<int>& heights) {
    std::stack<int> st;
    int n = heights.size();
    int maxArea = 0;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[i] < heights[st.top()]) {
            int top = st.top();
            st.pop();
            int width = st.empty()? i : i - st.top() - 1;
            int area = heights[top] * width;
            maxArea = std::max(maxArea, area);
        }
        st.push(i);
    }

    while (!st.empty()) {
        int top = st.top();
        st.pop();
        int width =st.empty()? n : n - st.top() - 1;
        int area =heights[top] * width;
        maxArea = std::max(maxArea, area);
    }

    return maxArea;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int testCase = 0; testCase < 10; ++testCase) {
        int n = rand() % 105 + 1;
        std::vector<int> randomHeights;
        for (int i = 0; i < n; ++i) {
            randomHeights.push_back(rand() % 105);
        }
        std::cout << "随机"<< testCase + 1 << " 输入: ";
        for (int h : randomHeights) {
            std::cout << h << " ";
        }
        std::cout << "\n随机" <<testCase + 1 <<" 输出: " << largestRectangleArea(randomHeights) << std::endl;
    }

    return 0;
}