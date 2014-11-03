/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_TIME_H_
#define _Z_CTK_BASE_TYPE_TIME_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_string.h"

#define CTK_USPS ctk::int64(1000000)

namespace ctk
{
    class CTK_API Time
    {
    public:
        struct Detail
        {
            int year_;
            int month_;
            int day_;
            int hour_;
            int minute_;
            int seconds_;
            int ms_;
            int us_;

            Detail();
            Detail(const Time& _input);
            Detail(rcistr _input, pcstr _format);

            // 格式串中的%依次代表年月日时分秒毫秒微秒，可以从后往前省略 //
            // 如 "%04d-%02d-%02d %02d:%02d:%02d.%03d" 生成 2009-01-01 12:00:00.123 //
            //    "%04d%02d%02d%02d%02d%02d" 生成 20090101120000 //
            void toString(ostr _result, pcstr _format) const;

            Time toTime() const;
        };

    public:
        Time();

        // No copy constructor and assignment operator necessary. The
        // automatically generated copy constructor and assignment
        // operator do the right thing.

        enum Clock { Realtime, Monotonic };
        CTK_STATIC_FUN Time now(Clock = Realtime);
        CTK_STATIC_FUN Time forever();
        CTK_STATIC_FUN Time seconds(int64);
        CTK_STATIC_FUN Time milliSeconds(int64);
        CTK_STATIC_FUN Time microSeconds(int64);

        operator timeval() const;

        void sleep() const;

        int64 toSeconds() const;
        int64 toMilliSeconds() const;
        int64 toMicroSeconds() const;

        double toSecondsDouble() const;
        double toMilliSecondsDouble() const;
        double toMicroSecondsDouble() const;

        void toFullDateTime(ctk::ostr _s) const;
        void toFullDateTime(String& _s) const;
        void toDateTime(ctk::ostr _s) const;
        void toDateTime(String& _s) const;
        String toFullDateTime() const;
        String toDateTime() const;
        String toDuration() const;
        String toString() const;

        // default format %04d-%02d-%02d %02d:%02d:%02d.%03d%03d
        //                YYYY-MM-DD hh:mm:ss.mmmuuu
        // may throw InvalidDataException
        void fromString(ctk::rcistr _s, pcstr _format=0);

        // 参见Detail注释 //
        void format(ctk::ostr _s, pcstr _format) const;
        void format(String& _s, pcstr _format) const;
        String format(pcstr _format) const;

        Detail toDetail() const { return Detail(*this); }

        Time operator-() const
        {
            return Time(-usec_);
        }

        Time operator-(const Time& rhs) const
        {
            return Time(usec_ - rhs.usec_);
        }

        Time operator+(const Time& rhs) const
        {
            return Time(usec_ + rhs.usec_);
        }

        Time& operator+=(const Time& rhs)
        {
            usec_ += rhs.usec_;
            return *this;
        }

        Time& operator-=(const Time& rhs)
        {
            usec_ -= rhs.usec_;
            return *this;
        }

        bool operator<(const Time& rhs) const
        {
            return usec_ < rhs.usec_;
        }

        bool operator<=(const Time& rhs) const
        {
            return usec_ <= rhs.usec_;
        }

        bool operator>(const Time& rhs) const
        {
            return usec_ > rhs.usec_;
        }

        bool operator>=(const Time& rhs) const
        {
            return usec_ >= rhs.usec_;
        }

        bool operator==(const Time& rhs) const
        {
            return usec_ == rhs.usec_;
        }

        bool operator!=(const Time& rhs) const
        {
            return usec_ != rhs.usec_;
        }

        double operator/(const Time& rhs) const
        {
            return (double)usec_ / (double)rhs.usec_;
        }

        Time& operator*=(int rhs)
        {
            usec_ *= rhs;
            return *this;
        }

        Time operator*(int rhs) const
        {
            Time t(*this);
            t *= rhs;
            return t;
        }

        Time& operator/=(int rhs)
        {
            usec_ /= rhs;
            return *this;
        }

        Time operator/(int rhs) const
        {
            Time t;
            t.usec_ = usec_ / rhs;
            return t;
        }

        Time& operator*=(int64 rhs)
        {
            usec_ *= rhs;
            return *this;
        }

        Time operator*(int64 rhs) const
        {
            Time t;
            t.usec_ = usec_ * rhs;
            return t;
        }

        Time& operator/=(int64 rhs)
        {
            usec_ /= rhs;
            return *this;
        }

        Time operator/(int64 rhs) const
        {
            Time t;
            t.usec_ = usec_ / rhs;
            return t;
        }

        Time& operator*=(double rhs)
        {
            usec_ = static_cast<int64>(static_cast<double>(usec_) * rhs);
            return *this;
        }

        Time operator*(double rhs) const
        {
            Time t;
            t.usec_ = static_cast<int64>(static_cast<double>(usec_) * rhs);
            return t;
        }

        Time& operator/=(double rhs)
        {
            usec_ = static_cast<int64>(static_cast<double>(usec_) / rhs);
            return *this;
        }

        Time operator/(double rhs) const
        {
            Time t;
            t.usec_ = static_cast<int64>(static_cast<double>(usec_) / rhs);
            return t;
        }

    private:
        Time(int64);

        int64 usec_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const Time& _v);

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_TIME_H_

