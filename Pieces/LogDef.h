
#define GOOGLE_LOG(LEVEL)                                                 \
	::google::protobuf::internal::LogFinisher() =                           \
	::google::protobuf::internal::LogMessage(                             \
	::google::protobuf::LOGLEVEL_##LEVEL, __FILE__, __LINE__)
#define GOOGLE_LOG_IF(LEVEL, CONDITION) \
	!(CONDITION) ? (void)0 : GOOGLE_LOG(LEVEL)

#define GOOGLE_CHECK(EXPRESSION) \
	GOOGLE_LOG_IF(FATAL, !(EXPRESSION)) << "CHECK failed: " #EXPRESSION ": "
#define GOOGLE_CHECK_EQ(A, B) GOOGLE_CHECK((A) == (B))
#define GOOGLE_CHECK_NE(A, B) GOOGLE_CHECK((A) != (B))
#define GOOGLE_CHECK_LT(A, B) GOOGLE_CHECK((A) <  (B))
#define GOOGLE_CHECK_LE(A, B) GOOGLE_CHECK((A) <= (B))
#define GOOGLE_CHECK_GT(A, B) GOOGLE_CHECK((A) >  (B))
#define GOOGLE_CHECK_GE(A, B) GOOGLE_CHECK((A) >= (B))

class LogMessage {
public:
	LogMessage(LogLevel level, const char* filename, int line);
	~LogMessage();

	LogMessage& operator<<(const std::string& value);
	LogMessage& operator<<(const char* value);
	LogMessage& operator<<(char value);
	LogMessage& operator<<(int value);
	LogMessage& operator<<(uint value);
	LogMessage& operator<<(long value);
	LogMessage& operator<<(unsigned long value);
	LogMessage& operator<<(double value);

private:
	friend class LogFinisher;
	void Finish();

	LogLevel level_;
	const char* filename_;
	int line_;
	std::string message_;
};

// Used to make the entire "LOG(BLAH) << etc." expression have a void return
// type and print a newline after each message.
class LogFinisher 
{
public:
	void operator=(LogMessage& other)
	{
		other.Finish();
	}
};

void DefaultLogHandler(LogLevel level, const char* filename, int line, const string& message) 
{
	static const char* level_names[] = { "INFO", "WARNING", "ERROR", "FATAL" };

	// We use fprintf() instead of cerr because we want this to work at static
	// initialization time.
	fprintf(stderr, "[libprotobuf %s %s:%d] %s\n",
		level_names[level], filename, line, message.c_str());
	fflush(stderr);  // Needed on MSVC.
}
