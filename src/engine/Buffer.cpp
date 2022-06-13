//
// Created by Jacopo Beragnoli on 16/04/22.
//

// libs
#include <cassert>
#include <cstring>

// includes
#include "../../include/engine/Buffer.h"

namespace Engine {
    //Returns the minimum instance size required to be compatible with devices minOffsetAlignment
    //
    // - instanceSize The size of an instance
    // - minOffsetAlignment The minimum required alignment, in bytes, for the offset member (eg
    //   minUniformBufferOffsetAlignment)
    //
    // - VkResult of the buffer mapping call
    VkDeviceSize Buffer::getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment) {
        if (minOffsetAlignment > 0) {
            return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
        }
        return instanceSize;
    }

    Buffer::Buffer(
            Engine::Device &device,
            VkDeviceSize instanceSize,
            uint32_t instanceCount,
            VkBufferUsageFlags usageFlags,
            VkMemoryPropertyFlags memoryPropertyFlags,
            VkDeviceSize minOffsetAlignment)
            : device{device},
              instanceSize{instanceSize},
              instanceCount{instanceCount},
              usageFlags{usageFlags},
              memoryPropertyFlags{memoryPropertyFlags} {
        alignmentSize = getAlignment(instanceSize, minOffsetAlignment);
        bufferSize = alignmentSize * instanceCount;
        device.createBuffer(bufferSize, usageFlags, memoryPropertyFlags, buffer, memory);
    }

    Buffer::~Buffer() {
        unmap();
        vkDestroyBuffer(device.getVkDevice(), buffer, nullptr);
        vkFreeMemory(device.getVkDevice(), memory, nullptr);
    }

    // Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
    //
    // - size (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete
    //   buffer range.
    // - offset (Optional) Byte offset from beginning
    //
    // - VkResult of the buffer mapping call
    VkResult Buffer::map(VkDeviceSize size, VkDeviceSize offset) {
        assert(buffer && memory && "Called map on buffer before create");
        return vkMapMemory(device.getVkDevice(), memory, offset, size, 0, &mapped);
    }

    // Unmap a mapped memory range
    //
    // Does not return a result as vkUnmapMemory can't fail
    void Buffer::unmap() {
        if (mapped) {
            vkUnmapMemory(device.getVkDevice(), memory);
            mapped = nullptr;
        }
    }

    // Copies the specified data to the mapped buffer. Default value writes whole buffer range
    //
    // - data Pointer to the data to copy
    // - size (Optional) Size of the data to copy. Pass VK_WHOLE_SIZE to flush the complete buffer
    //   range.
    // - offset (Optional) Byte offset from beginning of mapped region
    void Buffer::writeToBuffer(void *data, VkDeviceSize size, VkDeviceSize offset) {
        assert(mapped && "Cannot copy to unmapped buffer");

        if (size == VK_WHOLE_SIZE) {
            memcpy(mapped, data, bufferSize);
        } else {
            char *memOffset = (char *) mapped;
            memOffset += offset;
            memcpy(memOffset, data, size);
        }
    }

    // Flush a memory range of the buffer to make it visible to the getVkDevice
    //
    // - size (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the
    //   complete buffer range.
    // - offset (Optional) Byte offset from beginning
    //
    // - VkResult of the flush call
    VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(device.getVkDevice(), 1, &mappedRange);
    }

    // Invalidate a memory range of the buffer to make it visible to the host
    //
    // Only required for non-coherent memory
    //
    // - size (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate
    // the complete buffer range.
    // - offset (Optional) Byte offset from beginning
    //
    // - VkResult of the invalidated call
    VkResult Buffer::invalidate(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkInvalidateMappedMemoryRanges(device.getVkDevice(), 1, &mappedRange);
    }

    // Create a buffer info descriptor
    //
    // - size (Optional) Size of the memory range of the descriptor
    // - offset (Optional) Byte offset from beginning
    //
    // - VkDescriptorBufferInfo of specified offset and range
    VkDescriptorBufferInfo Buffer::descriptorInfo(VkDeviceSize size, VkDeviceSize offset) {
        return VkDescriptorBufferInfo{
                buffer,
                offset,
                size,
        };
    }

    // Copies "instanceSize" bytes of data to the mapped buffer at an offset of index // alignmentSize
    //
    // - data Pointer to the data to copy
    // - index Used in offset calculation
    void Buffer::writeToIndex(void *data, int index) {
        writeToBuffer(data, instanceSize, index * alignmentSize);
    }

    //  Flush the memory range at index // alignmentSize of the buffer to make it visible to the getVkDevice
    //
    // - index Used in offset calculation
    VkResult Buffer::flushIndex(int index) { return flush(alignmentSize, index * alignmentSize); }

    // Create a buffer info descriptor
    //
    // - index Specifies the region given by index // alignmentSize
    //
    // - VkDescriptorBufferInfo for instance at index
    VkDescriptorBufferInfo Buffer::descriptorInfoForIndex(int index) {
        return descriptorInfo(alignmentSize, index * alignmentSize);
    }

    // Invalidate a memory range of the buffer to make it visible to the host
    //
    // Only required for non-coherent memory
    //
    // - index Specifies the region to invalidate: index // alignmentSize
    //
    // - VkResult of the invalidated call
    VkResult Buffer::invalidateIndex(int index) {
        return invalidate(alignmentSize, index * alignmentSize);
    }
}
