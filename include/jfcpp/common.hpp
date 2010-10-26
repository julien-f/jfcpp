#ifndef H_JFCPP_COMMON
#define H_JFCPP_COMMON

#ifdef JFCPP_NO_NAMESPACE
#	define JFCPP_NAMESPACE_BEGIN
#	define JFCPP_NAMESPACE_END
#	define JFCPP_NS()
#else
#	define JFCPP_NAMESPACE_BEGIN namespace jfcpp {
#	define JFCPP_NAMESPACE_END } /* namespace jfcpp */
#	define JFCPP_NS() jfcpp::
#endif

#endif // H_JFCPP_COMMON
