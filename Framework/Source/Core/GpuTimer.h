/***************************************************************************
# Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#pragma once

#include <memory>

namespace Falcor
{
    /** Abstracts GPU timer queries. \n
        This class provides mechanism to get elapsed time in miliseconds between a pair of Begin()/End() calls.
    */
    class GpuTimer : public std::enable_shared_from_this<GpuTimer>
    {
    public:
        using SharedPtr = std::shared_ptr<GpuTimer>;
        using SharedConstPtr = std::shared_ptr<const GpuTimer>;

        /** create a new object
        */
        static SharedPtr create();

        /** Destroy a new object
        */
        ~GpuTimer();

        /** Begin the capture window. \n
            If begin() is called in the middle of a begin()/end() pair, it will be ignored and a warning will be logged.
        */
        void begin();

        /** Begin the capture window. \n
            If end() is called before a begin() was called, it will be ignored and a warning will be logged.
        */
        void end();

        /** Get the elapsed time between a pair of Begin()/End() calls. \n
            If this function called not after a Begin()/End() pair, false will be returned and a warning will be logged.
            \param[in] waitForResult - if true, will wait until the results are ready, otherwise will return even if the GPU query did not finish.
            \param[out] elapsedTime - if results are ready, will return the elapsed time, otherwise invalid
            \return - true if results are ready, false if query did not finish or the function was called but Begin()/End() was not called before.
        */
        bool getElapsedTime(bool waitForResult, float& elapsedTime);

    private:
        GpuTimer();
        bool mBeginCalled = false;
        bool mEndCalled = false;
        uint32_t mApiHandle[2];
    };
}