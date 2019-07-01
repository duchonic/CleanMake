inline bool checkIfNanOrInf(double value){
	return ( std::isnan(value) || std::isinf(value) );
}

inline bool checkIfNanOrInf(float value){
	return ( std::isnan(value) || std::isinf(value) );
}
