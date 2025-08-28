using System;

namespace Models.UserData
{
    public class UserData
    {
        private String uuid;
        private String username;

        public UserData()
        {
            Guid myuuid = Guid.NewGuid();
            this.uuid = myuuid.ToString();
        }

        public String getUUID()
        {
            return this.uuid;
        }

        public void setUsername(String username)
        {
            this.username = username;
        }
    }
}