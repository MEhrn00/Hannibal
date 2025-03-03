#include "config.h"


#ifdef INCLUDE_CMD_MV

#include "hannibal_tasking.h"


SECTION_CODE void cmd_mv(TASK t)
{
    HANNIBAL_INSTANCE_PTR

    CMD_MV *mv = (CMD_MV *)t.cmd;
    LPCWSTR src_path = mv->src_path;
    LPCWSTR dst_path = mv->dst_path;

    
    DWORD attributes = hannibal_instance_ptr->Win32.GetFileAttributesW(src_path);

    if (attributes == INVALID_FILE_ATTRIBUTES) {
        hannibal_response(L"Src does not exist", t.task_uuid);
        hannibal_instance_ptr->Win32.VirtualFree(mv->src_path, 0, MEM_RELEASE);
        hannibal_instance_ptr->Win32.VirtualFree(mv->dst_path, 0, MEM_RELEASE);
        hannibal_instance_ptr->Win32.VirtualFree(t.cmd, 0, MEM_RELEASE);
        return;
    }

    if (hannibal_instance_ptr->Win32.MoveFileExW(src_path, dst_path, 0)) { // No overwrite flag
        hannibal_response(L"Moved", t.task_uuid);
    } else { // TODO: Better error info
        hannibal_response(L"Error", t.task_uuid);
    }

    hannibal_instance_ptr->Win32.VirtualFree(mv->src_path, 0, MEM_RELEASE);
    hannibal_instance_ptr->Win32.VirtualFree(mv->dst_path, 0, MEM_RELEASE);
    hannibal_instance_ptr->Win32.VirtualFree(t.cmd, 0, MEM_RELEASE);
}

#endif