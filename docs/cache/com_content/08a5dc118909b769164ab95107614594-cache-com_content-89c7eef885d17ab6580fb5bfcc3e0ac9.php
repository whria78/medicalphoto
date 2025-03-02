<?php die("Access Denied"); ?>#x#a:4:{s:4:"body";s:8497:"<div class="item-page">

	<h2>
			<a href="/index.php/kr/faq-3">
		FAQ</a>
		</h2>








<h3>1. 기존에 관리하던 환자 사진 자료가 있는데 MedicalPhoto 에서 과거 사진을 사용할 수 있을까요?  </h3>
<h3>2. 이미 MedicalPhoto 를 설치했는데 기존의 사진을 옮길 수 있을까요? or 날짜순이 아닌 다른 이름의 폴더를 생성하고 싶습니다.</h3>
<h3>3. 병원이 여러 지점인데 다른 지점의 사진을 같이 관리 할 수 있을까요?   </h3>
<h3>4. 사진 정리할 때 환자 사진 다수를 한꺼번에 빠르게 선택 할 수 있는 방법이 있나요? </h3>
<h3>5. 사진을 Microsoft 파워포인트로 이동하고 싶습니다.</h3>
<h3>6. MedicalPhoto 가 먼 미래에 작동하지 않은 경우 가지고 있던 사진은 어떻게 되나요? </h3>
<h3>7. 다수의 사진을 한꺼번에 삭제하고 싶습니다.</h3>
<h3>8. MedicalPhoto 데이터를 백업을 하려면 어떻게 해야 하나요?</h3>
<h3>9. 설치, 관리 등 MedicalPhoto 에 관한 기술적인 지원을 받고 싶습니다.</h3>
<p> </p>
<p> </p>
<p> </p>
<h2>1. 기존에 관리하던 환자 사진 자료가 있는데 MedicalPhoto 에서 과거 사진을 사용할 수 있을까요?  </h2>
<p> </p>
<p>기존의 사진이</p>
<p>"d:/old_photo" 에 "d:/old_photo/홍길동/2011-1-1/IMG_1234.jpg"</p>
<p>식으로 정리되어 있다고 가정하고 MedicalPhoto를 설치하는 방법입니다.</p>
<p> </p>
<p>- "d:/임상사진" 폴더 생성합니다.</p>
<p>- "d:/임상사진/old_photo" 로 기존의 d:/old_photo 폴더를 이동합니다.</p>
<p>- MedicalPhoto 를 설치합니다.</p>
<p>- 설치 폴더는 "d:/임상사진" 으로 지정합니다.</p>
<p>- MedicalPhoto 의 검색창에 "홍길동" 으로 검색을 하면 old_photo 안에 있는 "홍길동"의 과거 사진(IMG_1234.jpg)을 찾아줍니다. 검색은 폴더명까지 포함해서 검색을 합니다.</p>
<p>- 아래와 같이 저장이 됩니다.</p>
<p><strong><em>임상사진</em></strong></p>
<p><strong><em>-   old_photo - 홍길동</em></strong></p>
<p><strong><em>-   2012</em></strong></p>
<p><strong><em>-   2011   </em></strong></p>
<p>   </p>
<p> </p>
<p><a href="http://www.youtube.com/v/EEm6bmePYVQ&amp;amp;fmt=22&amp;amp;hd=1&amp;amp;cc_load_policy=1" target="_blank">Youtube 동영상 보기 </a></p>
<p> </p>
<p> </p>
<h2>2. 이미 MedicalPhoto 를 설치했는데 기존의 사진을 옮길 수 있을까요? or 날짜순이 아닌 다른 이름의 폴더를 생성하고 싶습니다.</h2>
<p> </p>
<p><strong><em>임상사진</em></strong></p>
<p><strong><em>-   new_photo</em></strong></p>
<p><strong><em>-   2012</em></strong></p>
<p><strong><em>-   2011   </em></strong></p>
<p> </p>
<p>방식으로 저장하고 싶은 경우입니다.</p>
<p> </p>
<p>- MedicalPhoto 가 저장되는 폴더를 탐색기로 엽니다. (ex) d:/임상사진)</p>
<p>- 올리고 싶은 사진이 있는 폴더를 (ex) d:/new_photo) "d:/임상사진/new_photo" 와 같이 이동시킵니다. MedicalPhotoServer 가 자동으로 폴더의 변화를 탐색해서 사진의 정보를 저장합니다.</p>
<p>- MedicalPhoto 를 실행해서 검색해보면 new_photo 의 사진이 검색이 됩니다.    </p>
<p> </p>
<p><a href="http://www.youtube.com/v/dg1Ai9DPXRM&amp;amp;fmt=22&amp;amp;hd=1&amp;amp;cc_load_policy=1">Youtube 동영상 보기</a></p>
<p> </p>
<p>cf) 만약에 제대로 검색이 안되는 경우는 MedicalPhotoServer -&gt; Check Database 를 클릭해서 수동으로 사진정보를 얻게 만들 수 있습니다.  </p>
<p> </p>
<p> </p>
<h2>3. 병원이 여러 지점인데 다른 지점의 사진을 같이 관리 할 수 있을까요?    </h2>
<p> </p>
<p>서버가 있는 공유기의 9999 번 TCP port 를 서버 컴퓨터로 포워딩시키면 외부에서도 접속이 가능합니다.  </p>
<p>하지만 인터넷을 통한 사진 공유는 보안 문제 때문에 권장하지 않습니다.  </p>
<p> </p>
<p> </p>
<h2>4. 사진 정리할 때 환자 사진 여러장을 한꺼번에 선택 할 수 있는 방법이 있나요?</h2>
<p> </p>
<p>MedicalPhoto 에서 사진을 선택할 때 CTRL 키를 누른 상태에서 사진을 선택하면,</p>
<p>1) 비슷한 파일명 또는 정보를 가진 사진이 우선적으로 한꺼번에 선택이 되고</p>
<p>2) 앞 뒤로 10초정도로 비슷한 시간대에 찍힌 사진이 한꺼번에 선택이 됩니다.</p>
<p>대부분의 경우 환자 한명 사진을 찍고 쉬었다가 다음 환자를 찍기 때문에 CTRL 키를 누르고 사진을 선택하면 같은 환자 사진이 자동으로 선택이 됩니다.</p>
<p> </p>
<p>  </p>
<h2>5. 사진을 Microsoft 파워포인트로 이동하고 싶습니다.</h2>
<p> </p>
<p>사진을 파워포인트로 이동하고 확대해서 배치하는 작업은 시간이 오래 걸리는 단순 반복 작업입니다.</p>
<p>MedicalPhoto 에서 사진을 선택한 이후 오른쪽 클릭을 하면 Powerpoint 로 보내는 기능이 있습니다.</p>
<p>Template 모양에 맞춰서 사진을 자동으로 전송해 줍니다.</p>
<p>Template 는 Powerpoint 에서 수정이 가능하며 Template 모양대로 사진을 보내줍니다.</p>
<p>Powerpoint 로 보내는 기능은 컴퓨터에 Microsoft Powerpoint 가 설치되어 있어야 실행이 가능합니다.</p>
<p> </p>
<p> </p>
<h2>6. MedicalPhoto 가 먼 미래에 작동하지 않은 경우 가지고 있던 사진은 어떻게 되나요?</h2>
<p>MedicalPhoto 가 미래에 작동하지 않더라도 사진 파일은 하드디스크에 MedicalPhoto 에서 보여주는 대로 저장이 됩니다.</p>
<p> </p>
<p>MedicalPhoto 에서</p>
<p>"임상사진/2012/aaa"</p>
<p>로 보이는 파일은</p>
<p> </p>
<p>"d:/임상사진/2012/aaa.jpg"</p>
<p>과 같은 방식으로 하드디스크에 저장되어 있습니다.</p>
<p>사진이 있는 위치는 <em>시작-&gt;프로그램-&gt;MedicalPhoto-&gt;s_config.txt</em> 에서 확인이 가능합니다.</p>
<p> </p>
<p>환자 ID, 이름, 병명에 대한 정보까지는 파일명에 저장이 되기 때문에 추후 MedicalPhoto 를 사용하지 않더라도 사용이 가능합니다.</p>
<p> </p>
<p> </p>
<h2>7. 다수의 사진을 한꺼번에 삭제하고 싶습니다.</h2>
<p>다수의 사진을 한꺼번에 삭제하려면 직접 사진이 저장된 폴더로 가서 삭제하는 것이 빠릅니다.</p>
<p>d:/clinical_photo 내에 임상 사진이 저장된다면 윈도우 탐색기로 d:/clinical_photo 로 가서 지우고 싶은 파일을 직접 지우면 됩니다.</p>
<p>MedicalPhoto 는 폴더의 변화를 자동으로 감지하기 때문에 지워진 파일에 대한 정보도 같이 삭제됩니다.</p>
<p>만약 지워진 파일에 대한 정보가 MedicalPhoto 내에 남아있다면 MedicalPhotoServer 를 실행해서 "Check Database" 를 실행하면 됩니다.</p>
<p> </p>
<p> </p>
<h2>8. MedicalPhoto 데이터를 백업을 하려면 어떻게 해야 하나요?</h2>
<p>d:/clinical_photo 폴더가 사진이 저장되는 폴더라면</p>
<p>"<em><strong>d:/clinical_photo/clinical_photo.dat</strong></em>" 라는 파일이 생성됩니다.</p>
<p>이 파일이 MedicalPhoto 의 데이터베이스 파일입니다.</p>
<p>백업할때 같이 백업하고 나중에 복구할 때 폴더만 지정하면 자동으로 읽어들입니다.</p>
<p> </p>
<p> </p>
<h2>9. 설치, 관리 등 MedicalPhoto 에 관한 기술적인 지원을 받고 싶습니다.</h2>
<p><script type='text/javascript'>
 <!--
 var prefix = '&#109;a' + 'i&#108;' + '&#116;o';
 var path = 'hr' + 'ef' + '=';
 var addy75727 = 'whr&#105;&#97;78' + '&#64;';
 addy75727 = addy75727 + 'gm&#97;&#105;l' + '&#46;' + 'c&#111;m';
 var addy_text75727 = 'whr&#105;&#97;78' + '&#64;' + 'gm&#97;&#105;l' + '&#46;' + 'c&#111;m';
 document.write('<a ' + path + '\'' + prefix + ':' + addy75727 + '\'>');
 document.write(addy_text75727);
 document.write('<\/a>');
 //-->\n </script><script type='text/javascript'>
 <!--
 document.write('<span style=\'display: none;\'>');
 //-->
 </script>spambots으로부터 이메일 주소가 보호되었습니다. 보시려면 JavaScript를 활성화하세요.
 <script type='text/javascript'>
 <!--
 document.write('</');
 document.write('span>');
 //-->
 </script> 으로 연락주세요. ^^</p> 
	
</div>
";s:4:"head";a:10:{s:5:"title";s:3:"FAQ";s:11:"description";s:74:"medicalphoto,medical,image,management,software,dermatology,plastic surgery";s:4:"link";s:0:"";s:8:"metaTags";a:2:{s:10:"http-equiv";a:1:{s:12:"content-type";s:9:"text/html";}s:8:"standard";a:3:{s:8:"keywords";s:74:"medicalphoto,medical,image,management,software,dermatology,plastic surgery";s:6:"rights";N;s:6:"author";s:10:"Super User";}}s:5:"links";a:0:{}s:11:"styleSheets";a:0:{}s:5:"style";a:0:{}s:7:"scripts";a:3:{s:33:"/media/system/js/mootools-core.js";a:3:{s:4:"mime";s:15:"text/javascript";s:5:"defer";b:0;s:5:"async";b:0;}s:24:"/media/system/js/core.js";a:3:{s:4:"mime";s:15:"text/javascript";s:5:"defer";b:0;s:5:"async";b:0;}s:27:"/media/system/js/caption.js";a:3:{s:4:"mime";s:15:"text/javascript";s:5:"defer";b:0;s:5:"async";b:0;}}s:6:"script";a:1:{s:15:"text/javascript";s:76:"window.addEvent('load', function() {
				new JCaption('img.caption');
			});";}s:6:"custom";a:0:{}}s:7:"pathway";a:1:{i:0;O:8:"stdClass":2:{s:4:"name";s:3:"FAQ";s:4:"link";s:20:"index.php?Itemid=511";}}s:6:"module";a:0:{}}