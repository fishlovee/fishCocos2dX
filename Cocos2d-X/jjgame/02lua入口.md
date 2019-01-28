# 02lua入口

```lua
-- Hall.lua

G_DEBUG_INFO_NUM = 100;
g_nDebugInfoIndex = 1;
g_aszDebugInfo = {}
g_nDebugInfoCount = 0;


MY_Print= function(...)
  print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
  local str = string.format(...);
  local szDebugInfo = string.format("[%d] %s", getTickCount(), str);
  print(szDebugInfo);
  g_aszDebugInfo[g_nDebugInfoIndex] = szDebugInfo;
  g_nDebugInfoIndex = g_nDebugInfoIndex + 1;
  if (g_nDebugInfoIndex > G_DEBUG_INFO_NUM) then
    g_nDebugInfoIndex = 1;
  end
 -- print(string.format("[%s]%s",os.date("%m-%d %H:%M:%S",os.time()),string.format(...)))
end

function MY_Debug()
    local strDebug = "";
    local nStrCount = 0;
    for i = g_nDebugInfoIndex - 1, 1, -1 do
        if (g_aszDebugInfo[i] == nil) then
            break;
        end
        strDebug = strDebug .. "\n" ..g_aszDebugInfo[i];
        nStrCount = nStrCount + 1;
        if (nStrCount >= 20) then
            break;
        end
    end
    for i = 100, g_nDebugInfoIndex, -1 do
        if (nStrCount >= 20) then
            break;
        end

        if (g_aszDebugInfo[i] == nil) then
            break;
        end
        strDebug = strDebug + g_aszDebugInfo[i];
        nStrCount = nStrCount + 1;
    end
    return strDebug;
end

cclog = function(...)
  print(string.format(...))
 -- print(string.format("[%s]%s",os.date("%m-%d %H:%M:%S",os.time()),string.format(...)))
end
-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
	print("----------------------------------------")
	print("LUA ERROR: " .. tostring(msg) .. "\n")
	CJni:shareJni():showMessageBox("LUA ERROR: " .. tostring(msg) .. "\n")
	print(debug.traceback())
	CJni:shareJni():showMessageBox  (debug.traceback())
	print("----------------------------------------")
end

function initPersimmions()
  -- Android请求用户权限
  local function permissionCallback(nSize, strPermissionsResult)
    -- print("initPersimmions--->" .. tostring(nSize) .. ", ".. tostring(strPermissionsResult))
      --strPermissionsResult 格式: "android.permission.WRITE_EXTERNAL_STORAGE=0;android.permission.ACCESS_FINE_LOCATION=1", 0:成功，1失败
      require("HallControl"):instance():start()
  end

  CJni:shareJni():requestPermissions(permissionCallback, 4, "android.permission.READ_PHONE_STATE", "android.permission.RECORD_AUDIO", "android.permission.ACCESS_FINE_LOCATION", "android.permission.ACCESS_COARSE_LOCATION")
end

local function main()
	-- avoid memory leak
	collectgarbage("setpause", 300)
	collectgarbage("setstepmul", 5000)

  initPersimmions()

end

-- 执行main函数，
xpcall(main, __G__TRACKBACK__)
```