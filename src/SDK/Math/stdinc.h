#pragma once

#define SAFE_DEL_ARRAY(x) {\
							if (x != NULL)\
							 {\
								delete[] x;\
								x = NULL;\
							}\
						  }


