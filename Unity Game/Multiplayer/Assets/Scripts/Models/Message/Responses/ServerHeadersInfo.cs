using System;

namespace Models.Message.Server
{
    public class ServerHeadersInfo
    {
        private int contentLength;
        private String contentType;
        
        public ServerHeadersInfo(int contentLength, String contentType) {
            this.contentLength = contentLength;
            this.contentType = contentType;
        }

        public int getContentLength() {
            return contentLength;
        }

        public void setContentLength(int contentLength) {
            this.contentLength = contentLength;
        }

        public String getContentType() {
            return contentType;
        }

        public void setContentType(String contentType) {
            this.contentType = contentType;
        }

        public String getHeaders() {

            return Constants.CONTENT_LENGTH + Constants.COLON + this.getContentLength() + Constants.HEADER_SEPARATOR + Constants.CONTENT_TYPE + Constants.COLON + this.getContentType() + Constants.HEADER_DELIMITER;
        }
    }
}