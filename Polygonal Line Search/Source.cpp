#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
constexpr double EPS = 1e-6;
constexpr int MAX_LINE = 50;
std::vector<std::pair<double, double>> lines[MAX_LINE + 1]; //[0]‚ª‚à‚Æ‚Æ‚È‚éü

int main() {
	int n, m;
	while (std::cin >> n && n) {
		std::vector<int> identical;
		for (auto& x : lines) x.clear();
		for (int i = 0; i < n + 1; i++) {
			std::cin >> m;
			for (int j = 0; j < m; j++) {
				int x, y; std::cin >> x >> y;
				lines[i].push_back(std::make_pair(x, y));
			}
		}

		//‘S‚Ä’†‰›‚É•½sˆÚ“®
		for (int i = 0; i < n + 1; i++) {
			double minX = 999999, maxX = -999999, minY = 999999, maxY = -999999;
			for (auto& x : lines[i]) {
				minX = std::min(minX, x.first);
				maxX = std::max(maxX, x.first);
				minY = std::min(minY, x.second);
				maxY = std::max(maxY, x.second);
			}
			for (auto& x : lines[i]) {
				x.first -= (minX + maxX) / 2; x.second -= (minY + maxY) / 2;
			}
		}

		//‰ñ“]‚µ‚È‚ª‚ç”äŠr
		double angle = M_PI_2;
		for (int k = 0; k < 4; k++) {
			for (auto& x : lines[0]) {
				double nx = x.first, ny = x.second;
				nx = x.first * std::cos(angle) - x.second * std::sin(angle);
				ny = x.first * std::sin(angle) + x.second * std::cos(angle);
				x.first = nx; x.second = ny;
			}

			//‚Ç‚ê‚©‚Æˆê’v‚·‚é‚©Šm‚©‚ß‚é
			for (int i = 1; i < n + 1; i++) {
				//Ü‚ê‚é”‚ªˆá‚¤‚Ì‚Åˆê’v‚·‚é‚±‚Æ‚Í‚È‚¢
				if (lines[0].size() != lines[i].size()) continue;

				bool ok = true;
				for (int j = 0; j < lines[i].size(); j++) {
					if (!(std::abs(lines[i][j].first - lines[0][j].first) < EPS
						&& std::abs(lines[i][j].second - lines[0][j].second) < EPS)) {
						ok = false; break;
					}
				}
				if(!ok) {
					ok = true;
					for (int j = lines[i].size() - 1; j >= 0; j--) {
						if (!(std::abs(lines[i][j].first - lines[0][lines[0].size() - j - 1].first) < EPS
							&& std::abs(lines[i][j].second - lines[0][lines[0].size() - j - 1].second) < EPS)) {
							ok = false; break;
						}
					}
				}

				if (ok && std::find(identical.begin(), identical.end(), i) == identical.end()) {
					identical.push_back(i);
				}
			}
		}
		std::sort(identical.begin(), identical.end());
		for (auto& x : identical) std::cout << x << std::endl;
		std::cout << "+++++" << std::endl;
	}

	return 0;
}