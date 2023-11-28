// 여태까지 멀티 스레딩을 사용하는 여러가지 문법들을 배워봤다.
// 이번에는 멀티 스레딩으로 벡터 내적을 계산하는 예제를 통해서 실제 문법이 어떻게 사용이 되는 지 그리고 차이가 어떻게 나는 지 등등을 한 번 직접 실험하면서 살펴본다.

#include <iostream>
#include <chrono>
#include <mutex>
#include <random>
#include <thread>
#include <utility>
#include <vector>
#include <atomic>
#include <future>
#include <numeric>		// std::inner_product
#include <execution>	// parallel execution

using namespace std;

mutex mtx;
// mutex를 꼭 전역 변수로 선언할 필요는 없다. 여러 개의 스레드가 공통적으로 접근할 수 있는 scope에 있으면 된다.
// 그리고 mutex도 항상 존재할 필요는 없다. mutex로 lockguard를 만들어주고 싶은 부분이 작동할 때만 mutex가 살아있으면 된다.
// 그러니깐 코딩할 때 mutex를 어떤 클래스의 멤버로 집어넣어도 되고 scope에 넣어도 된다.

void dotProductNaive(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, unsigned long long& sum)
{
	for (unsigned i = i_start; i < i_end; ++i)
		sum += v0[i] * v1[i];
}

void dotProductLock(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, unsigned long long& sum)
{
	// std::scoped_lock lock(mtx);
	// 속도를 높이기 위해 scoped_lock을 for문 밖으로 옮기면 어떨까라고 생각할 수 있다.
	// scoped_lock이 작동하는 범위를 scope 전체가 되도록 옮기니깐 속도가 오히려 훨씬 빨라졌다.
	// 그러면 오히려 밖으로 빼면 되나 생각할 수 있는데 지금 cout으로 출력된 값을 보니깐 start, end, start, end, ... 이렇게 나왔다.
	// 이 전체가 lock이기 때문에 병렬이 아니라, 동시적으로 실행이 된 게 아니라 순차적으로 실행이 됐다는 의미이다.
	// 실제로 이런 방식으로 병렬처리를 하는 것은 의미가 없다는 거다.
	// 오히려 스레드를 생성하는 오버헤드만 커지게 된다.

	cout << "Thread start " << endl;

	for (unsigned i = i_start; i < i_end; ++i)
	{
		std::scoped_lock lock(mtx); // C++ 17
		// 초반에 말했었지만 scoped_lock은 영역이 작은 쪽에 들어가는게 좋은데 작은 영역에 들어오긴 했지만 너무 빈번하게 자주 실행이 되어버리면 오히려 느려진다.
		// 멀티 스레딩을 안 하느니만 못하는 최악의 결과가 나오게 된다. 그래서 멀티 스레딩을 처음 시도를 하는 경우에는 오히려 퍼포먼스가 떨어지거나 혹은 퍼포먼스는 안 떨어지는 대신에 결과가 나쁘거나 이런 식으로 작동이 될 수 있다.
		// 그런데 이것도 경우에 따라서 또 다르다. 락이 걸린 scope 전후로 어마어마하게 일이 많으면 상대적으로 멀티 스레딩의 효율이 높아지기도 하는데 일단은 극단적인 경우를 가지고 실수를 할 수 있는 부분에 대해서 먼저 설명을 했다.

		sum += v0[i] * v1[i];
	}

	cout << "Thread end " << endl;
}

void dotProductAtomic(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end, atomic<unsigned long long>& sum)
{
	for (unsigned i = i_start; i < i_end; ++i)
	{
		sum += v0[i] * v1[i];
		// atomic 연산이 일반연산보다 느리기 때문에 빈번하게 호출되는 곳에 atomic 연산을 넣어버리면 느려진다.
	}
}

auto dotProductFuture(const vector<int>& v0, const vector<int>& v1,
	const unsigned i_start, const unsigned i_end)
{
	int sum = 0; // local sum
	for (unsigned i = i_start; i < i_end; ++i)
	{
		sum += v0[i] * v1[i];
	}

	return sum;
}

int main()
{
	/*
		v0 = { 1, 2, 3 }
		v1 = { 4, 5, 6 }
		v0_dot_v1 = 1*4 + 2*5 + 3*6;
	*/

	const long long n_data = 100'000'000;
	const unsigned n_threads = 4;

	/* initialize vectors */
	std::vector<int> v0, v1;
	v0.reserve(n_data);
	v1.reserve(n_data);
	// reserve()로 push할 때의 효율을 높였다.

	random_device seed;
	mt19937 engine(seed());

	uniform_int_distribution<> uniformDist(1, 10);

	for (long long i = 0; i < n_data; ++i)
	{
		v0.push_back(uniformDist(engine));
		v1.push_back(uniformDist(engine));
	}

	cout << "std::inner_product" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		const auto sum = std::inner_product(v0.begin(), v0.end(), v1.begin(), 0ull);
		// auto인데도 unsigned long long으로 자동 추론을 할 수 있게 된 이유는 0을 0ull으로 표기를 해서 넣어줬기 때문이다.

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	// 멀티 스레딩 프로그래밍을 한다면 정답을 계산을 하고 그것과 정답이 맞는지 비교하고 그리고 퍼포먼스를 또 비교하는 방식으로 작업을 하는 것이 좋다.

	cout << "Naive" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = std::thread(dotProductNaive, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));

		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}
	// 스레드 개수를 임의의 개수로 사용할 수 있게 하기 위해서 조금 코드가 복잡해졌다.
	// 실행해보면 시간도 더 걸렸고 무엇보다 답이 틀리게 나온다. 레이스 컨디션 때문에 그렇다.
	// sum에다가 값을 더하고 있는데 여러 개의 스레드가 동시에 값을 건드리니깐 문제가 생겨서 값이 제대로 더해지지 않고 있다.

	// cout << "Lockguard" << endl;
	// {
	// 	const auto sta = chrono::steady_clock::now();

	// 	unsigned long long sum = 0;

	// 	vector<thread> threads;
	// 	threads.resize(n_threads);

	// 	const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t] = std::thread(dotProductLock, std::ref(v0), std::ref(v1),
	// 			t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t].join();

	// 	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	// 	cout << dur.count() << endl;
	// 	cout << sum << endl;
	// 	cout << endl;
	// }

	// cout << "Atomic" << endl;
	// {
	// 	const auto sta = chrono::steady_clock::now();

	// 	atomic<unsigned long long> sum = 0;

	// 	vector<thread> threads;
	// 	threads.resize(n_threads);

	// 	const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t] = std::thread(dotProductAtomic, std::ref(v0), std::ref(v1),
	// 			t * n_per_thread, (t + 1) * n_per_thread, std::ref(sum));

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t].join();

	// 	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	// 	cout << dur.count() << endl;
	// 	cout << sum << endl;
	// 	cout << endl;
	// }

	cout << "Future" << endl;   // 확실히 비동기 적으로 작업을 진행하는 것이 빠르다는 것을 알 수 있다.
	{
		const auto sta = chrono::steady_clock::now();

		unsigned long long sum = 0;

		vector<std::future<int>> futures;
		// unsigned long long으로 받지 않은 이유는 부분의 합은 integer 범위 안에 들어오기 때문이다.
		futures.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
		for (unsigned t = 0; t < n_threads; ++t)
			futures[t] = std::async(dotProductFuture, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread);
		// 전역 변수 역할을 하는 sum이 들어갈 필요가 없다. 왜냐하면 dotProductFuture()에서는 local sum을 계산해서 return 해주고 있기 때문이다.

		for (unsigned t = 0; t < n_threads; ++t)
			sum += futures[t].get();
		// .join()을 하는 대신에 .get()을 받아서 sum에다가 더해주고 있다.

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	// future 쓰는게 무조건 좋구나 thread 나빠 이렇게 생각할 수도 있다. 그런데 꼭 그렇진 않다.
	//TODO: use divide and conquer strategy for std::thread, std::thread & std::atomic
	//TODO: use divide and conquer strategy for std::thread & std::promise

	/* divide and conquer strategy for lockguard */
	cout << "Divide Lockguard" << endl;
	{
		const auto sta = chrono::steady_clock::now();

		vector<unsigned long long> divide_sum;
		divide_sum.resize(n_threads);

		vector<thread> threads;
		threads.resize(n_threads);

		const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
		for (unsigned t = 0; t < n_threads; ++t)
			threads[t] = std::thread(dotProductLock, std::ref(v0), std::ref(v1),
				t * n_per_thread, (t + 1) * n_per_thread, std::ref(divide_sum[t]));

		for (unsigned t = 0; t < n_threads; ++t)
			threads[t].join();

		unsigned long long sum = 0;

		for (unsigned t = 0; t < n_threads; ++t)
			sum += divide_sum[t];

		const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

		cout << dur.count() << endl;
		cout << sum << endl;
		cout << endl;
	}

	// /* divide and conquer strategy for atomic */
	// cout << "Divide Atomic" << endl;
	// {
	// 	const auto sta = chrono::steady_clock::now();

	// 	vector<atomic<unsigned long long>> divide_sum;
	// 	divide_sum.resize(n_threads);

	// 	vector<thread> threads;
	// 	threads.resize(n_threads);

	// 	const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t] = std::thread(dotProductAtomic, std::ref(v0), std::ref(v1),
	// 			t * n_per_thread, (t + 1) * n_per_thread, std::ref(divide_sum[t]));

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t].join();

	// 	unsigned long long sum = 0;

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		sum += divide_sum[t];

	// 	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	// 	cout << dur.count() << endl;
	// 	cout << sum << endl;
	// 	cout << endl;
	// }

	// /* divide and conquer strategy for promise */
	// cout << "Promise" << endl;
	// {
	// 	const auto sta = chrono::steady_clock::now();

	// 	unsigned long long sum = 0;

	// 	vector<std::promise<int>> proms;
	// 	proms.resize(n_threads);

	// 	vector<std::future<int>> futures;
	// 	futures.resize(n_threads);

	// 	vector<thread> threads;
	// 	threads.resize(n_threads);

	// 	const unsigned n_per_thread = n_data / n_threads; // assumes remainder = 0
	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 	{
	// 		futures[t] = proms[t].get_future();
	// 		threads[t] = std::thread([&](std::promise<int>&& prom)
	// 			{
	// 				prom.set_value(dotProductFuture(std::ref(v0), std::ref(v1), t* n_per_thread, (t + 1)* n_per_thread));
	// 			}, std::move(proms[t]));
	// 	}

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		sum += futures[t].get();

	// 	for (unsigned t = 0; t < n_threads; ++t)
	// 		threads[t].join();

	// 	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	// 	cout << dur.count() << endl;
	// 	cout << sum << endl;
	// 	cout << endl;
	// }

	// cout << "std::transform_reduce" << endl;
	// {
	// 	const auto sta = chrono::steady_clock::now();

	// 	//const auto sum = std::transform_reduce(std::execution::seq, v0.begin(), v0.end(), v1.begin(), 0ull);
	// 	const auto sum = std::transform_reduce(std::execution::par, v0.begin(), v0.end(), v1.begin(), 0ull);

	// 	const chrono::duration<double> dur = chrono::steady_clock::now() - sta;

	// 	cout << dur.count() << endl;
	// 	cout << sum << endl;
	// 	cout << endl;
	// }
	// std::inner_product의 병렬 버전이 std::transform_reduce()이다. std::transform_reduce() 말고도 std::sort() 같은 함수들이 전부 병렬 처리를 지원해준다. 그래서 기본적인 것들을 빠르게 구현할 때는 병렬 처리를 직접 구현할 필요는 없다.
	// 하지만 병렬 처리 함수들을 사용하기에 앞서 멀티 스레딩을 먼저 조금 알고 있으면 사용할 때 조금 더 유리할 거고 둘째로 std에서 만들어준 코드들이 모든 문제들을 전부 병렬 처리 해주지는 않는다. 그리고 여전히 병렬 처리했을 때 문제가 생길 여지가 분명히 존재한다.

	return 0;
}