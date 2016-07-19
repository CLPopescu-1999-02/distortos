/**
 * \file
 * \brief ChipSpiMasterLowLevel class header for STM32F4
 *
 * \author Copyright (C) 2016 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_CHIPSPIMASTERLOWLEVEL_HPP_
#define SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_CHIPSPIMASTERLOWLEVEL_HPP_

#include "distortos/devices/communication/SpiMasterBase.hpp"
#include "distortos/devices/communication/SpiMasterErrorSet.hpp"
#include "distortos/devices/communication/SpiMasterLowLevel.hpp"

#include "distortos/distortosConfiguration.h"

namespace distortos
{

namespace chip
{

/// ChipSpiMasterLowLevel class is a low-level SPI master driver for STM32F4
class ChipSpiMasterLowLevel : public devices::SpiMasterLowLevel
{
public:

	class Parameters;

#ifdef CONFIG_CHIP_HAS_SPI1

	/// parameters for construction of SPI master low-level driver for SPI1
	static const Parameters spi1parameters;

#endif	// def CONFIG_CHIP_HAS_SPI1

#ifdef CONFIG_CHIP_HAS_SPI2

	/// parameters for construction of SPI master low-level driver for SPI2
	static const Parameters spi2parameters;

#endif	// def CONFIG_CHIP_HAS_SPI2

#ifdef CONFIG_CHIP_HAS_SPI3

	/// parameters for construction of SPI master low-level driver for SPI3
	static const Parameters spi3parameters;

#endif	// def CONFIG_CHIP_HAS_SPI3

#ifdef CONFIG_CHIP_HAS_SPI4

	/// parameters for construction of SPI master low-level driver for SPI4
	static const Parameters spi4parameters;

#endif	// def CONFIG_CHIP_HAS_SPI4

#ifdef CONFIG_CHIP_HAS_SPI5

	/// parameters for construction of SPI master low-level driver for SPI5
	static const Parameters spi5parameters;

#endif	// def CONFIG_CHIP_HAS_SPI5

#ifdef CONFIG_CHIP_HAS_SPI6

	/// parameters for construction of SPI master low-level driver for SPI6
	static const Parameters spi6parameters;

#endif	// def CONFIG_CHIP_HAS_SPI6

	/**
	 * \brief ChipSpiMasterLowLevel's constructor
	 *
	 * \param [in] parameters is a reference to object with peripheral parameters
	 */

	constexpr explicit ChipSpiMasterLowLevel(const Parameters& parameters) :
			parameters_{parameters},
			spiMasterBase_{},
			readBuffer_{},
			writeBuffer_{},
			size_{},
			readPosition_{},
			writePosition_{},
			errorSet_{}
	{

	}

	/**
	 * \brief SpiMasterLowLevel's destructor
	 *
	 * Does nothing if driver is already stopped. If it's not, performs forced stop of operation.
	 */

	~ChipSpiMasterLowLevel() override;

	/**
	 * \brief Configures parameters of low-level SPI master driver.
	 *
	 * \param [in] mode is the desired SPI mode
	 * \param [in] clockFrequency is the desired clock frequency, Hz
	 * \param [in] wordLength selects word length, bits, {8, 16}
	 * \param [in] lsbFirst selects whether MSB (false) or LSB (true) is transmitted first
	 *
	 * \return pair with return code (0 on success, error code otherwise) and real clock frequency;
	 * error codes:
	 * - EBADF - the driver is not started;
	 * - EBUSY - transfer is in progress;
	 * - EINVAL - selected SPI mode and/or clock frequency and/or format are invalid;
	 */

	std::pair<int, uint32_t> configure(devices::SpiMode mode, uint32_t clockFrequency, uint8_t wordLength,
			bool lsbFirst) override;

	/**
	 * \brief Interrupt handler
	 *
	 * \note this must not be called by user code
	 */

	void interruptHandler();

	/**
	 * \brief Starts low-level SPI master driver.
	 *
	 * \param [in] spiMasterBase is a reference to SpiMasterBase object that will be associated with this one
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not stopped;
	 */

	int start(devices::SpiMasterBase& spiMasterBase) override;

	/**
	 * \brief Starts asynchronous transfer.
	 *
	 * This function returns immediately. When the transfer is physically finished (either expected number of bytes were
	 * written and read or an error was detected), SpiMasterBase::transferCompleteEvent() will be executed.
	 *
	 * \param [in] writeBuffer is the buffer with data that will be written, nullptr to send dummy data
	 * \param [out] readBuffer is the buffer with data that will be read, nullptr to ignore received data
	 * \param [in] size is the size of transfer (size of \a writeBuffer and/or \a readBuffer), bytes, must be even if
	 * number of data bits is in range (8; 16], divisible by 3 if number of data bits is in range (16; 24] or divisible
	 * by 4 if number of data bits is in range (24; 32]
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - transfer is in progress;
	 * - EINVAL - \a size is invalid;
	 */

	int startTransfer(const void* writeBuffer, void* readBuffer, size_t size) override;

	/**
	 * \brief Stops low-level SPI master driver.
	 *
	 * \return 0 on success, error code otherwise:
	 * - EBADF - the driver is not started;
	 * - EBUSY - transfer is in progress;
	 */

	int stop() override;

private:

	/**
	 * \return true if driver is started, false otherwise
	 */

	bool isStarted() const
	{
		return spiMasterBase_ != nullptr;
	}

	/**
	 * \return true if transfer is in progress, false otherwise
	 */

	bool isTransferInProgress() const
	{
		return size_ != 0;
	}

	/// reference to configuration parameters
	const Parameters& parameters_;

	/// pointer to SpiMasterBase object associated with this one
	devices::SpiMasterBase* spiMasterBase_;

	/// buffer to which the data is being written, nullptr to ignore received data
	uint8_t* volatile readBuffer_;

	/// buffer with data that is being transmitted, nullptr to send dummy data
	const uint8_t* volatile writeBuffer_;

	/// size of transfer (size of \a readBuffer_ and/or \a writeBuffer_), bytes
	volatile size_t size_;

	/// current position in \a readBuffer_
	volatile size_t readPosition_;

	/// current position in \a writeBuffer_
	volatile size_t writePosition_;

	/// current set of detected errors
	devices::SpiMasterErrorSet errorSet_;
};

}	// namespace chip

}	// namespace distortos

#endif	// SOURCE_CHIP_STM32_STM32F4_INCLUDE_DISTORTOS_CHIP_CHIPSPIMASTERLOWLEVEL_HPP_