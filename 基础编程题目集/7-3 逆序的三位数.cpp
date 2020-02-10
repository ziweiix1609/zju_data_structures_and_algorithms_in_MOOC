#include <iostream>
#include <stack>
using namespace std;
stack<int> st;
int main() {
	char s[1010];
	scanf("%s", s);
	for (int i = 0; i < strlen(s); i++)
		st.push(s[i] - '0');
	while (!st.empty()) {
		int t = st.top();
		st.pop();
		if (t == 0) continue;
		else printf("%d", t);
	}
	return 0;
}
