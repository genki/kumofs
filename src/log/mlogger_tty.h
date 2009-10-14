//
// kumofs
//
// Copyright (C) 2009 FURUHASHI Sadayuki
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
#ifndef MLOGGER_TTY_H__
#define MLOGGER_TTY_H__

#include "mlogger.h"

class mlogger_tty : public mlogger {
public:
	mlogger_tty(level runtime_level, std::ostream& stream);
	~mlogger_tty();

	void log_impl(level lv, std::string& str);

private:
	std::ostream& m_stream;
};

#endif /* mlogger_tty.h */

