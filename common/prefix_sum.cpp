// 二维矩阵的前缀和
// 计算过程非常优雅，多出一行一列，可以在计算前缀和和使用前缀和的时候不需要考虑各种边界情况。
vector<vector<int>> prefixSum(vector<vector<int>>& matrix) {
    vector<vector<int>> matPrefixSum(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matPrefixSum[i + 1][j + 1] = matPrefixSum[i + 1][j] + matPrefixSum[i][j + 1] -matPrefixSum[i][j] + matrix[i][j];
        }
    }
    return matPrefixSum;
}

// 二维前缀和的使用。
// 为更符合使用习惯，可以将这个四个坐标分别加加。
int sumRegion(vector<vector<int>>& matPrefixSum, int row1, int col1, int row2, int col2) {
    row1++, col1++, row2++, col2++;
    return matPrefixSum[row2][col2] - matPrefixSum[row1 - 1][col2] - matPrefixSum[row2][col1-1] + matPrefixSum[row1 - 1][col1-1];
}